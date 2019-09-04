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
struct TYPE_7__ {float* input; } ;
typedef  TYPE_1__ network ;
struct TYPE_8__ {int outputs; int batch; float* output; int inputs; float* weights; int /*<<< orphan*/  activation; int /*<<< orphan*/  biases; scalar_t__ batch_normalize; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  activate_array (float*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_bias (float*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  fill_cpu (int,int /*<<< orphan*/ ,float*,int) ; 
 int /*<<< orphan*/  forward_batchnorm_layer (TYPE_2__,TYPE_1__) ; 
 int /*<<< orphan*/  gemm (int /*<<< orphan*/ ,int,int,int,int,int,float*,int,float*,int,int,float*,int) ; 

void forward_connected_layer(layer l, network net)
{
    fill_cpu(l.outputs*l.batch, 0, l.output, 1);
    int m = l.batch;
    int k = l.inputs;
    int n = l.outputs;
    float *a = net.input;
    float *b = l.weights;
    float *c = l.output;
    gemm(0,1,m,n,k,1,a,k,b,k,1,c,n);
    if(l.batch_normalize){
        forward_batchnorm_layer(l, net);
    } else {
        add_bias(l.output, l.biases, l.batch, l.outputs, 1);
    }
    activate_array(l.output, l.outputs*l.batch, l.activation);
}