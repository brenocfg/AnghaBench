#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float learning_rate; float momentum; float decay; int batch; } ;
typedef  TYPE_1__ update_args ;
struct TYPE_6__ {float learning_rate_scale; int /*<<< orphan*/  weight_updates; int /*<<< orphan*/  nweights; int /*<<< orphan*/  weights; int /*<<< orphan*/  scale_updates; int /*<<< orphan*/  n; int /*<<< orphan*/  scales; int /*<<< orphan*/  bias_updates; int /*<<< orphan*/  biases; } ;
typedef  TYPE_2__ convolutional_layer ;

/* Variables and functions */
 int /*<<< orphan*/  axpy_cpu (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scal_cpu (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int) ; 

void update_convolutional_layer(convolutional_layer l, update_args a)
{
    float learning_rate = a.learning_rate*l.learning_rate_scale;
    float momentum = a.momentum;
    float decay = a.decay;
    int batch = a.batch;

    axpy_cpu(l.n, learning_rate/batch, l.bias_updates, 1, l.biases, 1);
    scal_cpu(l.n, momentum, l.bias_updates, 1);

    if(l.scales){
        axpy_cpu(l.n, learning_rate/batch, l.scale_updates, 1, l.scales, 1);
        scal_cpu(l.n, momentum, l.scale_updates, 1);
    }

    axpy_cpu(l.nweights, -decay*batch, l.weights, 1, l.weight_updates, 1);
    axpy_cpu(l.nweights, learning_rate/batch, l.weight_updates, 1, l.weights, 1);
    scal_cpu(l.nweights, momentum, l.weight_updates, 1);
}