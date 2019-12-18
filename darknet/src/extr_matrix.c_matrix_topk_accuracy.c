#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cols; int rows; scalar_t__** vals; } ;
typedef  TYPE_1__ matrix ;

/* Variables and functions */
 int* calloc (int,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  top_k (scalar_t__*,int,int,int*) ; 

float matrix_topk_accuracy(matrix truth, matrix guess, int k)
{
    int *indexes = calloc(k, sizeof(int));
    int n = truth.cols;
    int i,j;
    int correct = 0;
    for(i = 0; i < truth.rows; ++i){
        top_k(guess.vals[i], n, k, indexes);
        for(j = 0; j < k; ++j){
            int class = indexes[j];
            if(truth.vals[i][class]){
                ++correct;
                break;
            }
        }
    }
    free(indexes);
    return (float)correct/truth.rows;
}