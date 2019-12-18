#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {float* input; float* delta; float* truth; int /*<<< orphan*/  delta_gpu; int /*<<< orphan*/  input_gpu; } ;
typedef  TYPE_1__ network ;
struct TYPE_17__ {int outputs; int /*<<< orphan*/  delta_gpu; int /*<<< orphan*/  output_gpu; } ;
typedef  TYPE_2__ layer ;
struct TYPE_18__ {int w; int h; int c; float* data; } ;
typedef  TYPE_3__ image ;

/* Variables and functions */
 int /*<<< orphan*/  axpy_cpu (int,float,float*,int,float*,int) ; 
 int /*<<< orphan*/  axpy_gpu (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  backward_network (TYPE_1__*) ; 
 int /*<<< orphan*/  backward_network_gpu (TYPE_1__*) ; 
 int /*<<< orphan*/  constrain_image (TYPE_3__) ; 
 int /*<<< orphan*/  cuda_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuda_make_array (float*,int) ; 
 int /*<<< orphan*/  cuda_pull_array (int /*<<< orphan*/ ,float*,int) ; 
 int /*<<< orphan*/  cuda_push_array (int /*<<< orphan*/ ,float*,int) ; 
 int /*<<< orphan*/  forward_network (TYPE_1__*) ; 
 int /*<<< orphan*/  forward_network_gpu (TYPE_1__*) ; 
 int /*<<< orphan*/  free_image (TYPE_3__) ; 
 TYPE_2__ get_network_output_layer (TYPE_1__*) ; 
 float mag_array (float*,int) ; 
 TYPE_3__ make_image (int,int,int) ; 
 int /*<<< orphan*/  printf (char*,float) ; 
 int /*<<< orphan*/  scal_cpu (int,float,float*,int) ; 

void reconstruct_picture(network *net, float *features, image recon, image update, float rate, float momentum, float lambda, int smooth_size, int iters)
{
    int iter = 0;
    for (iter = 0; iter < iters; ++iter) {
        image delta = make_image(recon.w, recon.h, recon.c);

#ifdef GPU
        layer l = get_network_output_layer(net);
        cuda_push_array(net->input_gpu, recon.data, recon.w*recon.h*recon.c);
        //cuda_push_array(net->truth_gpu, features, net->truths);
        net->delta_gpu = cuda_make_array(delta.data, delta.w*delta.h*delta.c);

        forward_network_gpu(net);
        cuda_push_array(l.delta_gpu, features, l.outputs);
        axpy_gpu(l.outputs, -1, l.output_gpu, 1, l.delta_gpu, 1);
        backward_network_gpu(net);

        cuda_pull_array(net->delta_gpu, delta.data, delta.w*delta.h*delta.c);

        cuda_free(net->delta_gpu);
#else
        net->input = recon.data;
        net->delta = delta.data;
        net->truth = features;

        forward_network(net);
        backward_network(net);
#endif

        //normalize_array(delta.data, delta.w*delta.h*delta.c);
        axpy_cpu(recon.w*recon.h*recon.c, 1, delta.data, 1, update.data, 1);
        //smooth(recon, update, lambda, smooth_size);

        axpy_cpu(recon.w*recon.h*recon.c, rate, update.data, 1, recon.data, 1);
        scal_cpu(recon.w*recon.h*recon.c, momentum, update.data, 1);

        float mag = mag_array(delta.data, recon.w*recon.h*recon.c);
        printf("mag: %f\n", mag);
        //scal_cpu(recon.w*recon.h*recon.c, 600/mag, recon.data, 1);

        constrain_image(recon);
        free_image(delta);
    }
}