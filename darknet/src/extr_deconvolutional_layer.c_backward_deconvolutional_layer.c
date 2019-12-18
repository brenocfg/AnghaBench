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
struct TYPE_7__ {float* input; float* workspace; float* delta; } ;
typedef  TYPE_1__ network ;
struct TYPE_8__ {int outputs; int batch; int n; int out_w; int out_h; int c; int size; int h; int w; float* weight_updates; float* weights; int /*<<< orphan*/  pad; int /*<<< orphan*/  stride; int /*<<< orphan*/  out_c; scalar_t__ delta; int /*<<< orphan*/  bias_updates; scalar_t__ batch_normalize; int /*<<< orphan*/  activation; int /*<<< orphan*/  output; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  backward_batchnorm_layer (TYPE_2__,TYPE_1__) ; 
 int /*<<< orphan*/  backward_bias (int /*<<< orphan*/ ,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  gemm_cpu (int /*<<< orphan*/ ,int,int,int,int,int,float*,int,float*,int,int,float*,int) ; 
 int /*<<< orphan*/  gradient_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  im2col_cpu (scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 

void backward_deconvolutional_layer(layer l, network net)
{
    int i;

    gradient_array(l.output, l.outputs*l.batch, l.activation, l.delta);

    if(l.batch_normalize){
        backward_batchnorm_layer(l, net);
    } else {
        backward_bias(l.bias_updates, l.delta, l.batch, l.n, l.out_w*l.out_h);
    }

    //if(net.delta) memset(net.delta, 0, l.batch*l.h*l.w*l.c*sizeof(float));

    for(i = 0; i < l.batch; ++i){
        int m = l.c;
        int n = l.size*l.size*l.n;
        int k = l.h*l.w;

        float *a = net.input + i*m*k;
        float *b = net.workspace;
        float *c = l.weight_updates;

        im2col_cpu(l.delta + i*l.outputs, l.out_c, l.out_h, l.out_w, 
                l.size, l.stride, l.pad, b);
        gemm_cpu(0,1,m,n,k,1,a,k,b,k,1,c,n);

        if(net.delta){
            int m = l.c;
            int n = l.h*l.w;
            int k = l.size*l.size*l.n;

            float *a = l.weights;
            float *b = net.workspace;
            float *c = net.delta + i*n*m;

            gemm_cpu(0,0,m,n,k,1,a,k,b,n,1,c,n);
        }
    }
}