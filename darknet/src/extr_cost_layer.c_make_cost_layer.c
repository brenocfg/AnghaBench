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
struct TYPE_3__ {float scale; int batch; int inputs; int outputs; void* delta; void* output_gpu; void* output; void* delta_gpu; int /*<<< orphan*/  backward_gpu; int /*<<< orphan*/  forward_gpu; int /*<<< orphan*/  backward; int /*<<< orphan*/  forward; void* cost; int /*<<< orphan*/  cost_type; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ cost_layer ;
typedef  int /*<<< orphan*/  COST_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  COST ; 
 int /*<<< orphan*/  backward_cost_layer ; 
 int /*<<< orphan*/  backward_cost_layer_gpu ; 
 void* calloc (int,int) ; 
 void* cuda_make_array (void*,int) ; 
 int /*<<< orphan*/  forward_cost_layer ; 
 int /*<<< orphan*/  forward_cost_layer_gpu ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

cost_layer make_cost_layer(int batch, int inputs, COST_TYPE cost_type, float scale)
{
    fprintf(stderr, "cost                                           %4d\n",  inputs);
    cost_layer l = {0};
    l.type = COST;

    l.scale = scale;
    l.batch = batch;
    l.inputs = inputs;
    l.outputs = inputs;
    l.cost_type = cost_type;
    l.delta = calloc(inputs*batch, sizeof(float));
    l.output = calloc(inputs*batch, sizeof(float));
    l.cost = calloc(1, sizeof(float));

    l.forward = forward_cost_layer;
    l.backward = backward_cost_layer;
    #ifdef GPU
    l.forward_gpu = forward_cost_layer_gpu;
    l.backward_gpu = backward_cost_layer_gpu;

    l.delta_gpu = cuda_make_array(l.output, inputs*batch);
    l.output_gpu = cuda_make_array(l.delta, inputs*batch);
    #endif
    return l;
}