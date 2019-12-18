#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int batch; scalar_t__ t; int /*<<< orphan*/  eps; int /*<<< orphan*/  B2; int /*<<< orphan*/  B1; int /*<<< orphan*/  adam; int /*<<< orphan*/  decay; int /*<<< orphan*/  momentum; int /*<<< orphan*/  learning_rate; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ update_args ;
struct TYPE_10__ {scalar_t__ gpu_index; int batch; int subdivisions; int n; TYPE_3__* layers; scalar_t__* t; int /*<<< orphan*/  eps; int /*<<< orphan*/  B2; int /*<<< orphan*/  B1; int /*<<< orphan*/  adam; int /*<<< orphan*/  decay; int /*<<< orphan*/  momentum; } ;
typedef  TYPE_2__ network ;
struct TYPE_11__ {int /*<<< orphan*/  (* update ) (TYPE_3__,TYPE_1__) ;} ;
typedef  TYPE_3__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  get_current_rate (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__,TYPE_1__) ; 
 int /*<<< orphan*/  update_network_gpu (TYPE_2__*) ; 

void update_network(network *netp)
{
#ifdef GPU
    if(netp->gpu_index >= 0){
        update_network_gpu(netp);   
        return;
    }
#endif
    network net = *netp;
    int i;
    update_args a = {0};
    a.batch = net.batch*net.subdivisions;
    a.learning_rate = get_current_rate(netp);
    a.momentum = net.momentum;
    a.decay = net.decay;
    a.adam = net.adam;
    a.B1 = net.B1;
    a.B2 = net.B2;
    a.eps = net.eps;
    ++*net.t;
    a.t = *net.t;

    for(i = 0; i < net.n; ++i){
        layer l = net.layers[i];
        if(l.update){
            l.update(l, a);
        }
    }
}