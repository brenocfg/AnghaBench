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
struct TYPE_3__ {int inputs; int batch; int /*<<< orphan*/  rand; int /*<<< orphan*/  rand_gpu; } ;
typedef  TYPE_1__ dropout_layer ;

/* Variables and functions */
 int /*<<< orphan*/  cuda_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuda_make_array (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int) ; 

void resize_dropout_layer(dropout_layer *l, int inputs)
{
    l->rand = realloc(l->rand, l->inputs*l->batch*sizeof(float));
    #ifdef GPU
    cuda_free(l->rand_gpu);

    l->rand_gpu = cuda_make_array(l->rand, inputs*l->batch);
    #endif
}