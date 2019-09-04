#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int learning_rate_scale; int inputs; int outputs; int batch; int batch_normalize; int h; int w; int c; int out_h; int out_w; int out_c; float* weights; int* scales; int /*<<< orphan*/  activation; void* x_norm; void* x; void* rolling_variance; void* rolling_mean; void* variance_delta; void* variance; void* mean_delta; void* mean; void* scale_updates; void* scale_v; void* bias_v; void* scale_m; void* bias_m; void* v; void* m; scalar_t__* biases; int /*<<< orphan*/  update; int /*<<< orphan*/  backward; int /*<<< orphan*/  forward; void* bias_updates; void* weight_updates; void* delta; void* output; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ layer ;
typedef  int /*<<< orphan*/  ACTIVATION ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTED ; 
 int /*<<< orphan*/  backward_connected_layer ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  forward_connected_layer ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 float rand_uniform (int,int) ; 
 float sqrt (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  update_connected_layer ; 

layer make_connected_layer(int batch, int inputs, int outputs, ACTIVATION activation, int batch_normalize, int adam)
{
    int i;
    layer l = {0};
    l.learning_rate_scale = 1;
    l.type = CONNECTED;

    l.inputs = inputs;
    l.outputs = outputs;
    l.batch=batch;
    l.batch_normalize = batch_normalize;
    l.h = 1;
    l.w = 1;
    l.c = inputs;
    l.out_h = 1;
    l.out_w = 1;
    l.out_c = outputs;

    l.output = calloc(batch*outputs, sizeof(float));
    l.delta = calloc(batch*outputs, sizeof(float));

    l.weight_updates = calloc(inputs*outputs, sizeof(float));
    l.bias_updates = calloc(outputs, sizeof(float));

    l.weights = calloc(outputs*inputs, sizeof(float));
    l.biases = calloc(outputs, sizeof(float));

    l.forward = forward_connected_layer;
    l.backward = backward_connected_layer;
    l.update = update_connected_layer;

    //float scale = 1./sqrt(inputs);
    float scale = sqrt(2./inputs);
    for(i = 0; i < outputs*inputs; ++i){
        l.weights[i] = scale*rand_uniform(-1, 1);
    }

    for(i = 0; i < outputs; ++i){
        l.biases[i] = 0;
    }

    if(adam){
        l.m = calloc(l.inputs*l.outputs, sizeof(float));
        l.v = calloc(l.inputs*l.outputs, sizeof(float));
        l.bias_m = calloc(l.outputs, sizeof(float));
        l.scale_m = calloc(l.outputs, sizeof(float));
        l.bias_v = calloc(l.outputs, sizeof(float));
        l.scale_v = calloc(l.outputs, sizeof(float));
    }
    if(batch_normalize){
        l.scales = calloc(outputs, sizeof(float));
        l.scale_updates = calloc(outputs, sizeof(float));
        for(i = 0; i < outputs; ++i){
            l.scales[i] = 1;
        }

        l.mean = calloc(outputs, sizeof(float));
        l.mean_delta = calloc(outputs, sizeof(float));
        l.variance = calloc(outputs, sizeof(float));
        l.variance_delta = calloc(outputs, sizeof(float));

        l.rolling_mean = calloc(outputs, sizeof(float));
        l.rolling_variance = calloc(outputs, sizeof(float));

        l.x = calloc(batch*outputs, sizeof(float));
        l.x_norm = calloc(batch*outputs, sizeof(float));
    }

#ifdef GPU
    l.forward_gpu = forward_connected_layer_gpu;
    l.backward_gpu = backward_connected_layer_gpu;
    l.update_gpu = update_connected_layer_gpu;

    l.weights_gpu = cuda_make_array(l.weights, outputs*inputs);
    l.biases_gpu = cuda_make_array(l.biases, outputs);

    l.weight_updates_gpu = cuda_make_array(l.weight_updates, outputs*inputs);
    l.bias_updates_gpu = cuda_make_array(l.bias_updates, outputs);

    l.output_gpu = cuda_make_array(l.output, outputs*batch);
    l.delta_gpu = cuda_make_array(l.delta, outputs*batch);
    if (adam) {
        l.m_gpu =       cuda_make_array(0, inputs*outputs);
        l.v_gpu =       cuda_make_array(0, inputs*outputs);
        l.bias_m_gpu =  cuda_make_array(0, outputs);
        l.bias_v_gpu =  cuda_make_array(0, outputs);
        l.scale_m_gpu = cuda_make_array(0, outputs);
        l.scale_v_gpu = cuda_make_array(0, outputs);
    }

    if(batch_normalize){
        l.mean_gpu = cuda_make_array(l.mean, outputs);
        l.variance_gpu = cuda_make_array(l.variance, outputs);

        l.rolling_mean_gpu = cuda_make_array(l.mean, outputs);
        l.rolling_variance_gpu = cuda_make_array(l.variance, outputs);

        l.mean_delta_gpu = cuda_make_array(l.mean, outputs);
        l.variance_delta_gpu = cuda_make_array(l.variance, outputs);

        l.scales_gpu = cuda_make_array(l.scales, outputs);
        l.scale_updates_gpu = cuda_make_array(l.scale_updates, outputs);

        l.x_gpu = cuda_make_array(l.output, l.batch*outputs);
        l.x_norm_gpu = cuda_make_array(l.output, l.batch*outputs);
#ifdef CUDNN
        cudnnCreateTensorDescriptor(&l.normTensorDesc);
        cudnnCreateTensorDescriptor(&l.dstTensorDesc);
        cudnnSetTensor4dDescriptor(l.dstTensorDesc, CUDNN_TENSOR_NCHW, CUDNN_DATA_FLOAT, l.batch, l.out_c, l.out_h, l.out_w); 
        cudnnSetTensor4dDescriptor(l.normTensorDesc, CUDNN_TENSOR_NCHW, CUDNN_DATA_FLOAT, 1, l.out_c, 1, 1); 
#endif
    }
#endif
    l.activation = activation;
    fprintf(stderr, "connected                            %4d  ->  %4d\n", inputs, outputs);
    return l;
}