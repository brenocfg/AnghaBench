#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_11__ {size_t layers_num; int /*<<< orphan*/ * set_input_output; TYPE_1__* layers; void* model; } ;
struct TYPE_10__ {size_t activation; size_t input_num; size_t output_num; size_t kernel_size; size_t block_size; void** biases; void** kernel; } ;
struct TYPE_9__ {int type; TYPE_2__* params; int /*<<< orphan*/ * output; } ;
typedef  int /*<<< orphan*/  Layer ;
typedef  int /*<<< orphan*/  InputParams ;
typedef  TYPE_2__ DepthToSpaceParams ;
typedef  TYPE_3__ DNNModel ;
typedef  int DNNLayerType ;
typedef  TYPE_2__ ConvolutionalParams ;
typedef  TYPE_3__ ConvolutionalNetwork ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
#define  CONV 129 
#define  DEPTH_TO_SPACE 128 
 int INPUT ; 
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 
 void* av_int2float (scalar_t__) ; 
 void* av_malloc (int) ; 
 int /*<<< orphan*/  avio_closep (int /*<<< orphan*/ **) ; 
 scalar_t__ avio_open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_rl32 (int /*<<< orphan*/ *) ; 
 int avio_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_dnn_free_model_native (TYPE_3__**) ; 
 int /*<<< orphan*/  set_input_output_native ; 

DNNModel *ff_dnn_load_model_native(const char *model_filename)
{
    DNNModel *model = NULL;
    ConvolutionalNetwork *network = NULL;
    AVIOContext *model_file_context;
    int file_size, dnn_size, kernel_size, i;
    int32_t layer;
    DNNLayerType layer_type;
    ConvolutionalParams *conv_params;
    DepthToSpaceParams *depth_to_space_params;

    model = av_malloc(sizeof(DNNModel));
    if (!model){
        return NULL;
    }

    if (avio_open(&model_file_context, model_filename, AVIO_FLAG_READ) < 0){
        av_freep(&model);
        return NULL;
    }
    file_size = avio_size(model_file_context);

    network = av_malloc(sizeof(ConvolutionalNetwork));
    if (!network){
        avio_closep(&model_file_context);
        av_freep(&model);
        return NULL;
    }
    model->model = (void *)network;

    network->layers_num = 1 + (int32_t)avio_rl32(model_file_context);
    dnn_size = 4;

    network->layers = av_malloc(network->layers_num * sizeof(Layer));
    if (!network->layers){
        av_freep(&network);
        avio_closep(&model_file_context);
        av_freep(&model);
        return NULL;
    }

    for (layer = 0; layer < network->layers_num; ++layer){
        network->layers[layer].output = NULL;
        network->layers[layer].params = NULL;
    }
    network->layers[0].type = INPUT;
    network->layers[0].params = av_malloc(sizeof(InputParams));
    if (!network->layers[0].params){
        avio_closep(&model_file_context);
        ff_dnn_free_model_native(&model);
        return NULL;
    }

    for (layer = 1; layer < network->layers_num; ++layer){
        layer_type = (int32_t)avio_rl32(model_file_context);
        dnn_size += 4;
        switch (layer_type){
        case CONV:
            conv_params = av_malloc(sizeof(ConvolutionalParams));
            if (!conv_params){
                avio_closep(&model_file_context);
                ff_dnn_free_model_native(&model);
                return NULL;
            }
            conv_params->activation = (int32_t)avio_rl32(model_file_context);
            conv_params->input_num = (int32_t)avio_rl32(model_file_context);
            conv_params->output_num = (int32_t)avio_rl32(model_file_context);
            conv_params->kernel_size = (int32_t)avio_rl32(model_file_context);
            kernel_size = conv_params->input_num * conv_params->output_num *
                          conv_params->kernel_size * conv_params->kernel_size;
            dnn_size += 16 + (kernel_size + conv_params->output_num << 2);
            if (dnn_size > file_size || conv_params->input_num <= 0 ||
                conv_params->output_num <= 0 || conv_params->kernel_size <= 0){
                avio_closep(&model_file_context);
                ff_dnn_free_model_native(&model);
                return NULL;
            }
            conv_params->kernel = av_malloc(kernel_size * sizeof(float));
            conv_params->biases = av_malloc(conv_params->output_num * sizeof(float));
            if (!conv_params->kernel || !conv_params->biases){
                avio_closep(&model_file_context);
                ff_dnn_free_model_native(&model);
                return NULL;
            }
            for (i = 0; i < kernel_size; ++i){
                conv_params->kernel[i] = av_int2float(avio_rl32(model_file_context));
            }
            for (i = 0; i < conv_params->output_num; ++i){
                conv_params->biases[i] = av_int2float(avio_rl32(model_file_context));
            }
            network->layers[layer].type = CONV;
            network->layers[layer].params = conv_params;
            break;
        case DEPTH_TO_SPACE:
            depth_to_space_params = av_malloc(sizeof(DepthToSpaceParams));
            if (!depth_to_space_params){
                avio_closep(&model_file_context);
                ff_dnn_free_model_native(&model);
                return NULL;
            }
            depth_to_space_params->block_size = (int32_t)avio_rl32(model_file_context);
            dnn_size += 4;
            network->layers[layer].type = DEPTH_TO_SPACE;
            network->layers[layer].params = depth_to_space_params;
            break;
        default:
            avio_closep(&model_file_context);
            ff_dnn_free_model_native(&model);
            return NULL;
        }
    }

    avio_closep(&model_file_context);

    if (dnn_size != file_size){
        ff_dnn_free_model_native(&model);
        return NULL;
    }

    model->set_input_output = &set_input_output_native;

    return model;
}