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
struct TYPE_13__ {int output_num; } ;
struct TYPE_12__ {scalar_t__ model; } ;
struct TYPE_11__ {int block_size; } ;
struct TYPE_10__ {int width; int height; int channels; } ;
struct TYPE_9__ {int type; int /*<<< orphan*/  output; scalar_t__ params; } ;
typedef  TYPE_2__ InputParams ;
typedef  TYPE_3__ DepthToSpaceParams ;
typedef  int /*<<< orphan*/  DNNReturnType ;
typedef  TYPE_4__ DNNModel ;
typedef  TYPE_5__ ConvolutionalParams ;
typedef  TYPE_6__ ConvolutionalNetwork ;

/* Variables and functions */
#define  CONV 130 
#define  DEPTH_TO_SPACE 129 
 int /*<<< orphan*/  DNN_ERROR ; 
 int /*<<< orphan*/  DNN_SUCCESS ; 
#define  INPUT 128 
 int /*<<< orphan*/  convolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  depth_to_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

DNNReturnType ff_dnn_execute_model_native(const DNNModel *model)
{
    ConvolutionalNetwork *network = (ConvolutionalNetwork *)model->model;
    int cur_width, cur_height, cur_channels;
    int32_t layer;
    InputParams *input_params;
    ConvolutionalParams *conv_params;
    DepthToSpaceParams *depth_to_space_params;

    if (network->layers_num <= 0 || network->layers[0].type != INPUT || !network->layers[0].output){
        return DNN_ERROR;
    }
    else{
        input_params = (InputParams *)network->layers[0].params;
        cur_width = input_params->width;
        cur_height = input_params->height;
        cur_channels = input_params->channels;
    }

    for (layer = 1; layer < network->layers_num; ++layer){
        if (!network->layers[layer].output){
            return DNN_ERROR;
        }
        switch (network->layers[layer].type){
        case CONV:
            conv_params = (ConvolutionalParams *)network->layers[layer].params;
            convolve(network->layers[layer - 1].output, network->layers[layer].output, conv_params, cur_width, cur_height);
            cur_channels = conv_params->output_num;
            break;
        case DEPTH_TO_SPACE:
            depth_to_space_params = (DepthToSpaceParams *)network->layers[layer].params;
            depth_to_space(network->layers[layer - 1].output, network->layers[layer].output,
                           depth_to_space_params->block_size, cur_width, cur_height, cur_channels);
            cur_height *= depth_to_space_params->block_size;
            cur_width *= depth_to_space_params->block_size;
            cur_channels /= depth_to_space_params->block_size * depth_to_space_params->block_size;
            break;
        case INPUT:
            return DNN_ERROR;
        }
    }

    return DNN_SUCCESS;
}