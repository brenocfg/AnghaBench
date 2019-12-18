#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int n; int inputs; int w; int h; int /*<<< orphan*/  delta; int /*<<< orphan*/  input; scalar_t__ delta_gpu; TYPE_2__* layers; } ;
typedef  TYPE_1__ network ;
struct TYPE_21__ {int outputs; int /*<<< orphan*/  delta; int /*<<< orphan*/  output; scalar_t__ delta_gpu; int /*<<< orphan*/  output_gpu; } ;
typedef  TYPE_2__ layer ;
struct TYPE_22__ {float w; float h; int c; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ image ;

/* Variables and functions */
 int /*<<< orphan*/  axpy_cpu (int,float,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  backward_network (TYPE_1__*) ; 
 int /*<<< orphan*/  backward_network_gpu (TYPE_1__*) ; 
 int /*<<< orphan*/  calculate_loss (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float) ; 
 int /*<<< orphan*/  constrain_image (TYPE_3__) ; 
 int /*<<< orphan*/  copy_cpu (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_gpu (int,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 TYPE_3__ crop_image (TYPE_3__,int,int,float,float) ; 
 int /*<<< orphan*/  cuda_free (scalar_t__) ; 
 scalar_t__ cuda_make_array (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cuda_pull_array (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cuda_push_array (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fill_image (TYPE_3__,double) ; 
 int /*<<< orphan*/  flip_image (TYPE_3__) ; 
 int /*<<< orphan*/  forward_network (TYPE_1__*) ; 
 int /*<<< orphan*/  forward_network_gpu (TYPE_1__*) ; 
 int /*<<< orphan*/  free_image (TYPE_3__) ; 
 TYPE_3__ make_image (float,float,int) ; 
 int /*<<< orphan*/  normalize_array (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 
 int rand () ; 
 TYPE_3__ resize_image (TYPE_3__,int,int) ; 
 int /*<<< orphan*/  resize_network (TYPE_1__*,float,float) ; 

void optimize_picture(network *net, image orig, int max_layer, float scale, float rate, float thresh, int norm)
{
    //scale_image(orig, 2);
    //translate_image(orig, -1);
    net->n = max_layer + 1;

    int dx = rand()%16 - 8;
    int dy = rand()%16 - 8;
    int flip = rand()%2;

    image crop = crop_image(orig, dx, dy, orig.w, orig.h);
    image im = resize_image(crop, (int)(orig.w * scale), (int)(orig.h * scale));
    if(flip) flip_image(im);

    resize_network(net, im.w, im.h);
    layer last = net->layers[net->n-1];
    //net->layers[net->n - 1].activation = LINEAR;

    image delta = make_image(im.w, im.h, im.c);

#ifdef GPU
    net->delta_gpu = cuda_make_array(delta.data, im.w*im.h*im.c);
    copy_cpu(net->inputs, im.data, 1, net->input, 1);

    forward_network_gpu(net);
    copy_gpu(last.outputs, last.output_gpu, 1, last.delta_gpu, 1);

    cuda_pull_array(last.delta_gpu, last.delta, last.outputs);
    calculate_loss(last.delta, last.delta, last.outputs, thresh);
    cuda_push_array(last.delta_gpu, last.delta, last.outputs);

    backward_network_gpu(net);

    cuda_pull_array(net->delta_gpu, delta.data, im.w*im.h*im.c);
    cuda_free(net->delta_gpu);
    net->delta_gpu = 0;
#else
    printf("\nnet: %d %d %d im: %d %d %d\n", net->w, net->h, net->inputs, im.w, im.h, im.c);
    copy_cpu(net->inputs, im.data, 1, net->input, 1);
    net->delta = delta.data;
    forward_network(net);
    copy_cpu(last.outputs, last.output, 1, last.delta, 1);
    calculate_loss(last.output, last.delta, last.outputs, thresh);
    backward_network(net);
#endif

    if(flip) flip_image(delta);
    //normalize_array(delta.data, delta.w*delta.h*delta.c);
    image resized = resize_image(delta, orig.w, orig.h);
    image out = crop_image(resized, -dx, -dy, orig.w, orig.h);

    /*
       image g = grayscale_image(out);
       free_image(out);
       out = g;
     */

    //rate = rate / abs_mean(out.data, out.w*out.h*out.c);
    image gray = make_image(out.w, out.h, out.c);
    fill_image(gray, .5);
    axpy_cpu(orig.w*orig.h*orig.c, -1, orig.data, 1, gray.data, 1);
    axpy_cpu(orig.w*orig.h*orig.c, .1, gray.data, 1, out.data, 1);

    if(norm) normalize_array(out.data, out.w*out.h*out.c);
    axpy_cpu(orig.w*orig.h*orig.c, rate, out.data, 1, orig.data, 1);

    /*
       normalize_array(orig.data, orig.w*orig.h*orig.c);
       scale_image(orig, sqrt(var));
       translate_image(orig, mean);
     */

    //translate_image(orig, 1);
    //scale_image(orig, .5);
    //normalize_image(orig);

    constrain_image(orig);

    free_image(crop);
    free_image(im);
    free_image(delta);
    free_image(resized);
    free_image(out);

}