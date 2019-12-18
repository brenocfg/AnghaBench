#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ gpu_index; int n; int index; int /*<<< orphan*/  delta; int /*<<< orphan*/  input; TYPE_2__* layers; } ;
typedef  TYPE_1__ network ;
struct TYPE_8__ {int /*<<< orphan*/  (* backward ) (TYPE_2__,TYPE_1__) ;int /*<<< orphan*/  delta; int /*<<< orphan*/  output; scalar_t__ stopbackward; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  backward_network_gpu (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__,TYPE_1__) ; 

void backward_network(network *netp)
{
#ifdef GPU
    if(netp->gpu_index >= 0){
        backward_network_gpu(netp);   
        return;
    }
#endif
    network net = *netp;
    int i;
    network orig = net;
    for(i = net.n-1; i >= 0; --i){
        layer l = net.layers[i];
        if(l.stopbackward) break;
        if(i == 0){
            net = orig;
        }else{
            layer prev = net.layers[i-1];
            net.input = prev.output;
            net.delta = prev.delta;
        }
        net.index = i;
        l.backward(l, net);
    }
}