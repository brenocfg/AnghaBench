#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int n; float* cost; TYPE_1__* layers; } ;
typedef  TYPE_2__ network ;
struct TYPE_4__ {scalar_t__* cost; } ;

/* Variables and functions */

void calc_network_cost(network *netp)
{
    network net = *netp;
    int i;
    float sum = 0;
    int count = 0;
    for(i = 0; i < net.n; ++i){
        if(net.layers[i].cost){
            sum += net.layers[i].cost[0];
            ++count;
        }
    }
    *net.cost = sum/count;
}