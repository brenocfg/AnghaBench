#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float* input; scalar_t__ delta; int /*<<< orphan*/  workspace; } ;
typedef  TYPE_1__ network ;
struct TYPE_6__ {int out_w; int out_h; int outputs; int batch; float* delta; int w; int h; int c; int size; float* weight_updates; int n; float* weights; int /*<<< orphan*/  pad; int /*<<< orphan*/  stride; int /*<<< orphan*/  bias_updates; int /*<<< orphan*/  activation; int /*<<< orphan*/  output; } ;
typedef  TYPE_2__ local_layer ;

/* Variables and functions */
 int /*<<< orphan*/  axpy_cpu (int,int,float*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  col2im_cpu (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gemm (int,int,int,int,int,int,float*,int,float*,int,int,float*,int) ; 
 int /*<<< orphan*/  gradient_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  im2col_cpu (float*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void backward_local_layer(local_layer l, network net)
{
    int i, j;
    int locations = l.out_w*l.out_h;

    gradient_array(l.output, l.outputs*l.batch, l.activation, l.delta);

    for(i = 0; i < l.batch; ++i){
        axpy_cpu(l.outputs, 1, l.delta + i*l.outputs, 1, l.bias_updates, 1);
    }

    for(i = 0; i < l.batch; ++i){
        float *input = net.input + i*l.w*l.h*l.c;
        im2col_cpu(input, l.c, l.h, l.w, 
                l.size, l.stride, l.pad, net.workspace);

        for(j = 0; j < locations; ++j){ 
            float *a = l.delta + i*l.outputs + j;
            float *b = net.workspace + j;
            float *c = l.weight_updates + j*l.size*l.size*l.c*l.n;
            int m = l.n;
            int n = l.size*l.size*l.c;
            int k = 1;

            gemm(0,1,m,n,k,1,a,locations,b,locations,1,c,n);
        }

        if(net.delta){
            for(j = 0; j < locations; ++j){ 
                float *a = l.weights + j*l.size*l.size*l.c*l.n;
                float *b = l.delta + i*l.outputs + j;
                float *c = net.workspace + j;

                int m = l.size*l.size*l.c;
                int n = 1;
                int k = l.n;

                gemm(1,0,m,n,k,1,a,m,b,locations,0,c,locations);
            }

            col2im_cpu(net.workspace, l.c,  l.h,  l.w,  l.size,  l.stride, l.pad, net.delta+i*l.c*l.h*l.w);
        }
    }
}