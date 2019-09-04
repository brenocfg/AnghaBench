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
struct TYPE_7__ {float* input; float* workspace; } ;
typedef  TYPE_1__ network ;
struct TYPE_8__ {int size; int n; int h; int w; int c; int outputs; int batch; float* weights; int out_h; int out_w; int /*<<< orphan*/  activation; scalar_t__ output; int /*<<< orphan*/  biases; scalar_t__ batch_normalize; int /*<<< orphan*/  pad; int /*<<< orphan*/  stride; int /*<<< orphan*/  out_c; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  activate_array (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_bias (scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  col2im_cpu (float*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fill_cpu (int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  forward_batchnorm_layer (TYPE_2__ const,TYPE_1__) ; 
 int /*<<< orphan*/  gemm_cpu (int,int /*<<< orphan*/ ,int,int,int,int,float*,int,float*,int,int /*<<< orphan*/ ,float*,int) ; 

void forward_deconvolutional_layer(const layer l, network net)
{
    int i;

    int m = l.size*l.size*l.n;
    int n = l.h*l.w;
    int k = l.c;

    fill_cpu(l.outputs*l.batch, 0, l.output, 1);

    for(i = 0; i < l.batch; ++i){
        float *a = l.weights;
        float *b = net.input + i*l.c*l.h*l.w;
        float *c = net.workspace;

        gemm_cpu(1,0,m,n,k,1,a,m,b,n,0,c,n);

        col2im_cpu(net.workspace, l.out_c, l.out_h, l.out_w, l.size, l.stride, l.pad, l.output+i*l.outputs);
    }
    if (l.batch_normalize) {
        forward_batchnorm_layer(l, net);
    } else {
        add_bias(l.output, l.biases, l.batch, l.n, l.out_w*l.out_h);
    }
    activate_array(l.output, l.batch*l.n*l.out_w*l.out_h, l.activation);
}