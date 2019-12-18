#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  size_t int32_t ;
struct TYPE_7__ {TYPE_1__* biases; TYPE_1__* kernel; } ;
struct TYPE_6__ {size_t layers_num; scalar_t__ type; size_t operands_num; struct TYPE_6__* output_indexes; struct TYPE_6__* operands; struct TYPE_6__* data; struct TYPE_6__* layers; struct TYPE_6__* params; scalar_t__ model; } ;
typedef  TYPE_1__ DNNModel ;
typedef  TYPE_2__ ConvolutionalParams ;
typedef  TYPE_1__ ConvolutionalNetwork ;

/* Variables and functions */
 scalar_t__ DLT_CONV2D ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

void ff_dnn_free_model_native(DNNModel **model)
{
    ConvolutionalNetwork *network;
    ConvolutionalParams *conv_params;
    int32_t layer;

    if (*model)
    {
        network = (ConvolutionalNetwork *)(*model)->model;
        for (layer = 0; layer < network->layers_num; ++layer){
            if (network->layers[layer].type == DLT_CONV2D){
                conv_params = (ConvolutionalParams *)network->layers[layer].params;
                av_freep(&conv_params->kernel);
                av_freep(&conv_params->biases);
            }
            av_freep(&network->layers[layer].params);
        }
        av_freep(&network->layers);

        for (uint32_t operand = 0; operand < network->operands_num; ++operand)
            av_freep(&network->operands[operand].data);
        av_freep(&network->operands);

        av_freep(&network->output_indexes);
        av_freep(&network);
        av_freep(model);
    }
}