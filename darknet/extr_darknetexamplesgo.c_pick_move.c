#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int row; int col; int value; int mcts; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ move ;
struct TYPE_8__ {int* visit_count; double result; int* mean; double* prior; TYPE_1__** children; int /*<<< orphan*/  board; } ;
typedef  TYPE_3__ mcts_tree ;
struct TYPE_6__ {double result; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,double,double,float,int,double,int) ; 
 int max_index (float*,int) ; 
 int nind ; 
 double pow (int,int) ; 
 int /*<<< orphan*/  print_board (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int sample_array (float*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  top_k (float*,int,int,int*) ; 

move pick_move(mcts_tree *tree, float temp, int player)
{
    int i;
    float probs[19*19+1] = {0};
    move m = {0};
    double sum = 0;
    /*
    for(i = 0; i < 19*19+1; ++i){
        probs[i] = tree->visit_count[i];
    }
    */
    //softmax(probs, 19*19+1, temp, 1, probs);
    for(i = 0; i < 19*19+1; ++i){
        sum += pow(tree->visit_count[i], 1./temp);
    }
    for(i = 0; i < 19*19+1; ++i){
        probs[i] = pow(tree->visit_count[i], 1./temp) / sum;
    }

    int index = sample_array(probs, 19*19+1);
    m.row = index / 19;
    m.col = index % 19;
    m.value = (tree->result+1.)/2.;
    m.mcts  = (tree->mean[index]+1.)/2.;

    int indexes[nind];
    top_k(probs, 19*19+1, nind, indexes);
    print_board(stderr, tree->board, player, indexes);

    fprintf(stderr, "%d %d, Result: %f, Prior: %f, Prob: %f, Mean Value: %f, Child Result: %f, Visited: %d\n", index/19, index%19, tree->result, tree->prior[index], probs[index], tree->mean[index], (tree->children[index])?tree->children[index]->result:0, tree->visit_count[index]);
    int ind = max_index(probs, 19*19+1);
    fprintf(stderr, "%d %d, Result: %f, Prior: %f, Prob: %f, Mean Value: %f, Child Result: %f, Visited: %d\n", ind/19, ind%19, tree->result, tree->prior[ind], probs[ind], tree->mean[ind], (tree->children[ind])?tree->children[ind]->result:0, tree->visit_count[ind]);
    ind = max_index(tree->prior, 19*19+1);
    fprintf(stderr, "%d %d, Result: %f, Prior: %f, Prob: %f, Mean Value: %f, Child Result: %f, Visited: %d\n", ind/19, ind%19, tree->result, tree->prior[ind], probs[ind], tree->mean[ind], (tree->children[ind])?tree->children[ind]->result:0, tree->visit_count[ind]);
    return m;
}