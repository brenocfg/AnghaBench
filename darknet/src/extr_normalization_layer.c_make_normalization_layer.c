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
struct TYPE_3__ {int batch; int h; int out_h; int w; int out_w; int c; int out_c; float kappa; int size; float alpha; float beta; int inputs; int outputs; void* norms; void* norms_gpu; void* squared; void* squared_gpu; void* delta; void* delta_gpu; void* output; void* output_gpu; int /*<<< orphan*/  backward_gpu; int /*<<< orphan*/  forward_gpu; int /*<<< orphan*/  backward; int /*<<< orphan*/  forward; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  NORMALIZATION ; 
 int /*<<< orphan*/  backward_normalization_layer ; 
 int /*<<< orphan*/  backward_normalization_layer_gpu ; 
 void* calloc (int,int) ; 
 void* cuda_make_array (void*,int) ; 
 int /*<<< orphan*/  forward_normalization_layer ; 
 int /*<<< orphan*/  forward_normalization_layer_gpu ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

layer make_normalization_layer(int batch, int w, int h, int c, int size, float alpha, float beta, float kappa)
{
    fprintf(stderr, "Local Response Normalization Layer: %d x %d x %d image, %d size\n", w,h,c,size);
    layer layer = {0};
    layer.type = NORMALIZATION;
    layer.batch = batch;
    layer.h = layer.out_h = h;
    layer.w = layer.out_w = w;
    layer.c = layer.out_c = c;
    layer.kappa = kappa;
    layer.size = size;
    layer.alpha = alpha;
    layer.beta = beta;
    layer.output = calloc(h * w * c * batch, sizeof(float));
    layer.delta = calloc(h * w * c * batch, sizeof(float));
    layer.squared = calloc(h * w * c * batch, sizeof(float));
    layer.norms = calloc(h * w * c * batch, sizeof(float));
    layer.inputs = w*h*c;
    layer.outputs = layer.inputs;

    layer.forward = forward_normalization_layer;
    layer.backward = backward_normalization_layer;
    #ifdef GPU
    layer.forward_gpu = forward_normalization_layer_gpu;
    layer.backward_gpu = backward_normalization_layer_gpu;

    layer.output_gpu =  cuda_make_array(layer.output, h * w * c * batch);
    layer.delta_gpu =   cuda_make_array(layer.delta, h * w * c * batch);
    layer.squared_gpu = cuda_make_array(layer.squared, h * w * c * batch);
    layer.norms_gpu =   cuda_make_array(layer.norms, h * w * c * batch);
    #endif
    return layer;
}