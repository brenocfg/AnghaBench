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
struct TYPE_5__ {int n; TYPE_1__* layers; } ;
typedef  TYPE_2__ network ;
struct TYPE_4__ {scalar_t__ type; float alpha; float beta; } ;

/* Variables and functions */
 scalar_t__ SHORTCUT ; 

void set_network_alpha_beta(network *net, float alpha, float beta)
{
    int i;
    for(i = 0; i < net->n; ++i){
        if(net->layers[i].type == SHORTCUT){
            net->layers[i].alpha = alpha;
            net->layers[i].beta = beta;
        }
    }
}