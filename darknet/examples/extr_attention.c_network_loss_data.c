#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int batch; float* input; float* truth; int n; int outputs; TYPE_1__* layers; int /*<<< orphan*/  delta; scalar_t__ train; } ;
typedef  TYPE_4__ network ;
struct TYPE_16__ {float** vals; } ;
typedef  TYPE_5__ matrix ;
struct TYPE_14__ {int cols; int /*<<< orphan*/ * vals; } ;
struct TYPE_13__ {int rows; int cols; int /*<<< orphan*/ * vals; } ;
struct TYPE_17__ {TYPE_3__ y; TYPE_2__ X; } ;
typedef  TYPE_6__ data ;
struct TYPE_12__ {float* output; } ;

/* Variables and functions */
 float* calloc (int,int) ; 
 int /*<<< orphan*/  forward_network (TYPE_4__*) ; 
 int /*<<< orphan*/  free (float*) ; 
 TYPE_5__ make_matrix (int,int) ; 
 int max_index (float*,int) ; 
 int /*<<< orphan*/  memcpy (float*,int /*<<< orphan*/ ,int) ; 
 float sum_array (float*,int) ; 

matrix network_loss_data(network *net, data test)
{
    int i,b;
    int k = 1;
    matrix pred = make_matrix(test.X.rows, k);
    float *X = calloc(net->batch*test.X.cols, sizeof(float));
    float *y = calloc(net->batch*test.y.cols, sizeof(float));
    for(i = 0; i < test.X.rows; i += net->batch){
        for(b = 0; b < net->batch; ++b){
            if(i+b == test.X.rows) break;
            memcpy(X+b*test.X.cols, test.X.vals[i+b], test.X.cols*sizeof(float));
            memcpy(y+b*test.y.cols, test.y.vals[i+b], test.y.cols*sizeof(float));
        }

        network orig = *net;
        net->input = X;
        net->truth = y;
        net->train = 0;
        net->delta = 0;
        forward_network(net);
        *net = orig;

        float *delta = net->layers[net->n-1].output;
        for(b = 0; b < net->batch; ++b){
            if(i+b == test.X.rows) break;
            int t = max_index(y + b*test.y.cols, 1000);
            float err = sum_array(delta + b*net->outputs, net->outputs);
            pred.vals[i+b][0] = -err;
            //pred.vals[i+b][0] = 1-delta[b*net->outputs + t];
        }
    }
    free(X);
    free(y);
    return pred;   
}