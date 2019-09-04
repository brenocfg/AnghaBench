#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network ;
struct TYPE_3__ {float* board; float* mean; int* value; int total_count; float result; scalar_t__* prior; scalar_t__* visit_count; void* prob; void* children; } ;
typedef  TYPE_1__ mcts_tree ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  copy_cpu (int,float*,int,scalar_t__*,int) ; 
 float* network_predict_rotations (int /*<<< orphan*/ *,float*) ; 
 scalar_t__ occupied (float*,int) ; 

mcts_tree *expand(float *next, float *ko, network *net)
{
    mcts_tree *root = calloc(1, sizeof(mcts_tree));
    root->board = next;
    root->children = calloc(19*19+1, sizeof(mcts_tree*));
    root->prior = calloc(19*19 + 1, sizeof(float));
    root->prob = calloc(19*19 + 1, sizeof(float));
    root->mean = calloc(19*19 + 1, sizeof(float));
    root->value = calloc(19*19 + 1, sizeof(float));
    root->visit_count = calloc(19*19 + 1, sizeof(int));
    root->total_count = 1;
    int i;
    float *pred = network_predict_rotations(net, next);
    copy_cpu(19*19+1, pred, 1, root->prior, 1);
    float val = 2*pred[19*19 + 1] - 1;
    root->result = val;
    for(i = 0; i < 19*19+1; ++i) {
        root->visit_count[i] = 0;
        root->value[i] = 0;
        root->mean[i] = val;
        if(i < 19*19 && occupied(next, i)){
            root->value[i] = -1;
            root->mean[i] = -1;
            root->prior[i] = 0;
        }
    }
    //print_board(stderr, next, flip?-1:1, 0);
    return root;
}