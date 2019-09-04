#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double learning_rate; double momentum; double decay; } ;
typedef  TYPE_1__ network ;
struct TYPE_8__ {int n; char** data; } ;
typedef  TYPE_2__ moves ;

/* Variables and functions */
 char* basecfg (char*) ; 
 float* calloc (int,int) ; 
 TYPE_2__ load_go_moves (char*) ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 int max_index (float*,int) ; 
 int /*<<< orphan*/  predict_move2 (TYPE_1__*,float*,float*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_batch_network (TYPE_1__*,int) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_to_board (char*,float*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

void valid_go(char *cfgfile, char *weightfile, int multi, char *filename)
{
    srand(time(0));
    char *base = basecfg(cfgfile);
    printf("%s\n", base);
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);
    printf("Learning Rate: %g, Momentum: %g, Decay: %g\n", net->learning_rate, net->momentum, net->decay);

    float *board = calloc(19*19*3, sizeof(float));
    float *move = calloc(19*19+2, sizeof(float));
    // moves m = load_go_moves("/home/pjreddie/backup/go.test");
    moves m = load_go_moves(filename);

    int N = m.n;
    int i,j;
    int correct = 0;
    for (i = 0; i <N; ++i) {
        char *b = m.data[i];
        int player = b[0] - '0';
        //int result = b[1] - '0';
        int row = b[2];
        int col = b[3];
        int truth = col + 19*row;
        string_to_board(b+4, board);
        if(player > 0) for(j = 0; j < 19*19; ++j) board[19*19*2 + j] = 1;
        predict_move2(net, board, move, multi);
        int index = max_index(move, 19*19+1);
        if(index == truth) ++correct;
        printf("%d Accuracy %f\n", i, (float) correct/(i+1));
    }
}