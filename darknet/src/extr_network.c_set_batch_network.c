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
struct TYPE_5__ {int batch; int n; TYPE_2__* layers; } ;
typedef  TYPE_1__ network ;
struct TYPE_6__ {int batch; scalar_t__ type; int out_h; int out_w; int /*<<< orphan*/  out_c; int /*<<< orphan*/  normTensorDesc; int /*<<< orphan*/  dstTensorDesc; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 scalar_t__ CONVOLUTIONAL ; 
 int /*<<< orphan*/  CUDNN_DATA_FLOAT ; 
 int /*<<< orphan*/  CUDNN_TENSOR_NCHW ; 
 scalar_t__ DECONVOLUTIONAL ; 
 int /*<<< orphan*/  cudnnSetTensor4dDescriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cudnn_convolutional_setup (TYPE_2__*) ; 

void set_batch_network(network *net, int b)
{
    net->batch = b;
    int i;
    for(i = 0; i < net->n; ++i){
        net->layers[i].batch = b;
#ifdef CUDNN
        if(net->layers[i].type == CONVOLUTIONAL){
            cudnn_convolutional_setup(net->layers + i);
        }
        if(net->layers[i].type == DECONVOLUTIONAL){
            layer *l = net->layers + i;
            cudnnSetTensor4dDescriptor(l->dstTensorDesc, CUDNN_TENSOR_NCHW, CUDNN_DATA_FLOAT, 1, l->out_c, l->out_h, l->out_w);
            cudnnSetTensor4dDescriptor(l->normTensorDesc, CUDNN_TENSOR_NCHW, CUDNN_DATA_FLOAT, 1, l->out_c, 1, 1); 
        }
#endif
    }
}