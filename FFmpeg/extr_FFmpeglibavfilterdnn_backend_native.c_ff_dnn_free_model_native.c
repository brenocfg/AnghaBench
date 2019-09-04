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
typedef  size_t int32_t ;
struct TYPE_7__ {TYPE_1__* biases; TYPE_1__* kernel; } ;
struct TYPE_6__ {size_t layers_num; scalar_t__ type; struct TYPE_6__* layers; struct TYPE_6__* params; struct TYPE_6__* output; scalar_t__ model; } ;
typedef  TYPE_1__ DNNModel ;
typedef  TYPE_2__ ConvolutionalParams ;
typedef  TYPE_1__ ConvolutionalNetwork ;

/* Variables and functions */
 scalar_t__ CONV ; 
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
            av_freep(&network->layers[layer].output);
            if (network->layers[layer].type == CONV){
                conv_params = (ConvolutionalParams *)network->layers[layer].params;
                av_freep(&conv_params->kernel);
                av_freep(&conv_params->biases);
            }
            av_freep(&network->layers[layer].params);
        }
        av_freep(&network->layers);
        av_freep(&network);
        av_freep(model);
    }
}