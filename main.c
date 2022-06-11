#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdlib.h>
#define MAX_ROW 9
#define MAX_COLUMN 9
#define MAX 20


int data[9][9] = {
        {1,0,0,0,1,0,1,1,0},
        {1,1,0,1,1,1,0,0,1},
        {0,1,0,1,1,0,1,0,1},
        {0,1,1,0,0,1,0,1,1},
        {0,0,1,0,1,0,1,0,0},
        {1,1,1,0,0,0,0,1,1},
        {1,0,1,1,1,1,1,0,0},
        {1,1,1,0,0,0,1,0,1},
        {0,0,0,1,1,1,1,1,0}
    };

typedef struct POINT
{
    int row;
    int column;
    int value;
    bool visited;
   struct POINT *prev;
}point_t;
point_t matrix[MAX_ROW][MAX_COLUMN];

  // cau truc hang cho

typedef struct {
       point_t data[MAX];  // luu tru cac nut
       int front;          // chi so dau cua hang cho
       int rear;         // chi so cuoi cua hang cho
}Queue;

    // Khoi tao hang cho

void initQueue(Queue *q) {
       q->front = 0;
       q->rear = -1;
}

    //Kiem tra hang cho co rong hay khong

int isEmpty(Queue *q) {

       return (q->rear < q->front);

}
    // Kiem tra hang cho da day chua

int isFull(Queue q) {
    if(q.rear == MAX - 1) {
        return 1;
    }
       else return 0;

}

    // Them phan tu vao cuoi hang cho

void enQueue(Queue *q, point_t x)
{
    if (!isFull(*q))
    {
           if(q->rear == MAX - 1)
            {
                  for(int i = q->front; i <= q->rear; i++)
                  {
                           q->data[i - q->front] = q->data[i];
                  }
                  q->rear = MAX - q->front;
                  q->front = 0;
            }
            q->rear = q->rear + 1;
            q->data[q->rear] = x;
    }
}

    //  Lay phan tu dau tien ra khoi hang cho

point_t deQueue(Queue *q)
{
    point_t d;
    if (!isEmpty(q))
    {
       d = q->data[q->front];
       q->front = q->front +1;
    }
    if (q->front > q->rear)
    {
        initQueue(q);
    };
    return d;
}

    // Kiem tra diem nhap vao co nam trong ma tran hay khong

bool checkCoordinate(int x, int y) {

    bool ret = false;
    if ((0 <= x && x < 9) && (0 <= y && y < 9)) {       // dieu kien kiem tra la 0<=x<=9, 0<=y<=9
			ret = true;                                 // thoa man thi gan ret = true
    }
    return ret;                                         // neu khong thoa man thi tra ve ret voi value la false

}

    // In ma tran ra man hinh

void printMatrix(){
	int i, j;
    for( i=0;i<MAX_ROW;i++){
        for(j=0;j<MAX_COLUMN;j++){
            printf(" %d",data[i][j]);
            matrix[i][j].value = data[i][j];            // In ma tran ra man hinh
            matrix[i][j].column = j;                    // gan cac gia tri tuong ung vao mang 2 chieu matrix
            matrix[i][j].row = i;
            matrix[i][j].visited = false;
        }
        printf("\n");
    }
}

    // Kiem tra cac diem xung quanh diem duoc xet co thuoc trong ma tran va co value la 1 hay khong

void findSurroundingPoint(int x, int y, point_t surroundingPnt[4], int* count){
                int tempCnt = 0;                                        // khoi tao bien dem va gan gia tri 0
                if ((checkCoordinate(x, y+1) == true) && (matrix[x][y+1].value == 1)){
                    surroundingPnt[tempCnt] = matrix[x][y+1];           // kiem tra diem ben phai
                    tempCnt++;

                }
                if ((checkCoordinate(x+1, y) == true) && (matrix[x+1][y].value == 1)) {
                    surroundingPnt[tempCnt] = matrix[x+1][y];           // kiem tra diem ben duoi
					 tempCnt++;

                }
                if ((checkCoordinate(x, y-1) == true) && (matrix[x][y-1].value == 1)) {
                    surroundingPnt[tempCnt] = matrix[x][y-1];           // kiem tra diem ben trai
					tempCnt++;

                }
                if ((checkCoordinate(x-1, y) == true) && (matrix[x-1][y].value == 1)) {
			        surroundingPnt[tempCnt] = matrix[x-1][y];           // kiem tra diem ben tren
                    tempCnt++;

                }

             *count = tempCnt;
}

    // Tim duong di ngan nhat

void findShortestPath (int x, int y)
{
    if(checkCoordinate(x,y) == true && matrix[x][y].value == 1)      // kiem tra 2 diem x, y
    {

        Queue queue;                            // Khai bao hang doi
        initQueue(&queue);                      // goi ham initQueue()
        matrix[0][0].visited = true;            // danh dau diem (0,0) da di qua
        enQueue(&queue,matrix[0][0]);           // dua nut (0,0) vao hang doi
        point_t p;
        point_t pp[4];
        int count;
        bool found = false;
        printf("\n - Cac diem tu (0,0) den (%d, %d) co value la 1\n",x,y);
        printf("(0,0)");
        while((isEmpty(&queue) == false) && found == false)                 // dieu kien hang doi chua rong va chua tim thay diem dich
        {
            p = deQueue(&queue);                                            // lay phan tu p dau tien cua hang doi
            findSurroundingPoint(p.row,p.column,pp,&count);                 // kiem tra cac nut xung quanh nut p nhap vao
            int i;
            for( i=0;i<count;i++)                                           // vong lap for duyet cac nut vua tim thay o tren
            {
                if(pp[i].visited == false)                                  // neu nut chua di qua
                {
                    matrix[pp[i].row][pp[i].column].visited = true;         // danh dau da di qua
                    matrix[pp[i].row][pp[i].column].prev = &matrix[p.row][p.column]; // con tro *prev tro toi nut p
                    printf("-(%d,%d)",pp[i].row,pp[i].column);
                    if(pp[i].row == x && pp[i].column == y)                 // neu nut duoc duyet co value hang vot trung voi x, y nhap vao
                     {
                        found = true;               // gan found = true
                        break;                      // thoat khoi vong lap for
                     }else
                     {
                        enQueue(&queue,pp[i]);      // dua nut pp[i] vao hang doi va tiep tuc vong lap
                     }
                }
            }
        }

        if(found == true)
        {
            int count = 0;                              // tra bien dem ve 0 de dem so buoc
            point_t *destination = &matrix[x][y];           //con tro destination tro tro den diem cuoi duoc tim thay o tren
            printf("\n\n - Duong di ngan nhat tu (0,0) den (%d,%d) la: \n",x,y);
            while (destination->prev != NULL)       // trong khi c  on tro prev con ton tai
                {
                    printf("(%d,%d)-", destination->row, destination->column);       // in hang, cot ra man hinh
                    destination = destination->prev;        // tro den nut truoc cua nut hien tai
                    count++;                                // tang bien dem
                }
                printf("(0,0)");
                printf("\n\n - So buoc: %d",count);
        } else
            {
                printf("\n\n - Khong co duong di tu (0,0) den (%d,%d).", x,y);
            }
    }else
    printf("Toa do nhap vao ma tran khong hop le, khong tim duoc duong di!!!");

}


int main()
{
    printMatrix();
    printf("-------------------\n");
    int x,y;

    printf("Nhap toa do x,y.\n  x = ");
    scanf("%d",&x);

    printf("  y = ");
    scanf("%d",&y);

    findShortestPath(x,y);
    printf("\n");
    return 0;
}
