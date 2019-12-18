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
struct TYPE_3__ {float probability; int inputs; int outputs; int batch; int scale; int /*<<< orphan*/  rand; int /*<<< orphan*/  rand_gpu; int /*<<< orphan*/  backward_gpu; int /*<<< orphan*/  forward_gpu; int /*<<< orphan*/  backward; int /*<<< orphan*/  forward; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ dropout_layer ;

/* Variables and functions */
 int /*<<< orphan*/  DROPOUT ; 
 int /*<<< orphan*/  backward_dropout_layer ; 
 int /*<<< orphan*/  backward_dropout_layer_gpu ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int /*<<< orphan*/  cuda_make_array (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  forward_dropout_layer ; 
 int /*<<< orphan*/  forward_dropout_layer_gpu ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,float,int,int) ; 
 int /*<<< orphan*/  stderr ; 

dropout_layer make_dropout_layer(int batch, int inputs, float probability)
{
    dropout_layer l = {0};
    l.type = DROPOUT;
    l.probability = probability;
    l.inputs = inputs;
    l.outputs = inputs;
    l.batch = batch;
    l.rand = calloc(inputs*batch, sizeof(float));
    l.scale = 1./(1.-probability);
    l.forward = forward_dropout_layer;
    l.backward = backward_dropout_layer;
    #ifdef GPU
    l.forward_gpu = forward_dropout_layer_gpu;
    l.backward_gpu = backward_dropout_layer_gpu;
    l.rand_gpu = cuda_make_array(l.rand, inputs*batch);
    #endif
    fprintf(stderr, "dropout       p = %.2f               %4d  ->  %4d\n", probability, inputs, inputs);
    return l;
}