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
struct TYPE_3__ {int w; int h; int out_w; int scale; int out_h; int inputs; int c; int outputs; int out_c; int batch; int /*<<< orphan*/  output; int /*<<< orphan*/  output_gpu; } ;
typedef  TYPE_1__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  cuda_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuda_make_array (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int) ; 

void resize_crop_layer(layer *l, int w, int h)
{
    l->w = w;
    l->h = h;

    l->out_w =  l->scale*w;
    l->out_h =  l->scale*h;

    l->inputs = l->w * l->h * l->c;
    l->outputs = l->out_h * l->out_w * l->out_c;

    l->output = realloc(l->output, l->batch*l->outputs*sizeof(float));
    #ifdef GPU
    cuda_free(l->output_gpu);
    l->output_gpu = cuda_make_array(l->output, l->outputs*l->batch);
    #endif
}