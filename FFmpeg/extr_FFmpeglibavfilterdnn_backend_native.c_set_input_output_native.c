#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_14__ {size_t layers_num; TYPE_1__* layers; } ;
struct TYPE_13__ {int input_num; int output_num; } ;
struct TYPE_12__ {int width; int height; int channels; void* data; } ;
struct TYPE_11__ {int block_size; } ;
struct TYPE_10__ {int width; int height; int channels; } ;
struct TYPE_9__ {int type; void* output; scalar_t__ params; } ;
typedef  TYPE_2__ InputParams ;
typedef  TYPE_3__ DepthToSpaceParams ;
typedef  int /*<<< orphan*/  DNNReturnType ;
typedef  TYPE_4__ DNNData ;
typedef  TYPE_5__ ConvolutionalParams ;
typedef  TYPE_6__ ConvolutionalNetwork ;

/* Variables and functions */
#define  CONV 129 
#define  DEPTH_TO_SPACE 128 
 int /*<<< orphan*/  DNN_ERROR ; 
 int /*<<< orphan*/  DNN_SUCCESS ; 
 int INPUT ; 
 int /*<<< orphan*/  av_freep (void**) ; 
 void* av_malloc (int) ; 

__attribute__((used)) static DNNReturnType set_input_output_native(void *model, DNNData *input, DNNData *output)
{
    ConvolutionalNetwork *network = (ConvolutionalNetwork *)model;
    InputParams *input_params;
    ConvolutionalParams *conv_params;
    DepthToSpaceParams *depth_to_space_params;
    int cur_width, cur_height, cur_channels;
    int32_t layer;

    if (network->layers_num <= 0 || network->layers[0].type != INPUT){
        return DNN_ERROR;
    }
    else{
        input_params = (InputParams *)network->layers[0].params;
        input_params->width = cur_width = input->width;
        input_params->height = cur_height = input->height;
        input_params->channels = cur_channels = input->channels;
        if (input->data){
            av_freep(&input->data);
        }
        network->layers[0].output = input->data = av_malloc(cur_height * cur_width * cur_channels * sizeof(float));
        if (!network->layers[0].output){
            return DNN_ERROR;
        }
    }

    for (layer = 1; layer < network->layers_num; ++layer){
        switch (network->layers[layer].type){
        case CONV:
            conv_params = (ConvolutionalParams *)network->layers[layer].params;
            if (conv_params->input_num != cur_channels){
                return DNN_ERROR;
            }
            cur_channels = conv_params->output_num;
            break;
        case DEPTH_TO_SPACE:
            depth_to_space_params = (DepthToSpaceParams *)network->layers[layer].params;
            if (cur_channels % (depth_to_space_params->block_size * depth_to_space_params->block_size) != 0){
                return DNN_ERROR;
            }
            cur_channels = cur_channels / (depth_to_space_params->block_size * depth_to_space_params->block_size);
            cur_height *= depth_to_space_params->block_size;
            cur_width *= depth_to_space_params->block_size;
            break;
        default:
            return DNN_ERROR;
        }
        if (network->layers[layer].output){
            av_freep(&network->layers[layer].output);
        }
        network->layers[layer].output = av_malloc(cur_height * cur_width * cur_channels * sizeof(float));
        if (!network->layers[layer].output){
            return DNN_ERROR;
        }
    }

    output->data = network->layers[network->layers_num - 1].output;
    output->height = cur_height;
    output->width = cur_width;
    output->channels = cur_channels;

    return DNN_SUCCESS;
}