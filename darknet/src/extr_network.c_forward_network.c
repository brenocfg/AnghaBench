#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ gpu_index; int n; int index; int /*<<< orphan*/  truth; int /*<<< orphan*/  input; TYPE_2__* layers; } ;
typedef  TYPE_1__ network ;
struct TYPE_9__ {int outputs; int batch; int /*<<< orphan*/  output; scalar_t__ truth; int /*<<< orphan*/  (* forward ) (TYPE_2__,TYPE_1__) ;scalar_t__ delta; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  calc_network_cost (TYPE_1__*) ; 
 int /*<<< orphan*/  fill_cpu (int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  forward_network_gpu (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__,TYPE_1__) ; 

void forward_network(network *netp)
{
#ifdef GPU
    if(netp->gpu_index >= 0){
        forward_network_gpu(netp);   
        return;
    }
#endif
    network net = *netp;
    int i;
    for(i = 0; i < net.n; ++i){
        net.index = i;
        layer l = net.layers[i];
        if(l.delta){
            fill_cpu(l.outputs * l.batch, 0, l.delta, 1);
        }
        l.forward(l, net);
        net.input = l.output;
        if(l.truth) {
            net.truth = l.output;
        }
    }
    calc_network_cost(netp);
}