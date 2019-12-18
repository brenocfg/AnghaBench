#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* seen; int batch; int train; float* cost; int subdivisions; } ;
typedef  TYPE_1__ network ;

/* Variables and functions */
 int /*<<< orphan*/  backward_network (TYPE_1__*) ; 
 int /*<<< orphan*/  forward_network (TYPE_1__*) ; 
 int /*<<< orphan*/  update_network (TYPE_1__*) ; 

float train_network_datum(network *net)
{
    *net->seen += net->batch;
    net->train = 1;
    forward_network(net);
    backward_network(net);
    float error = *net->cost;
    if(((*net->seen)/net->batch)%net->subdivisions == 0) update_network(net);
    return error;
}