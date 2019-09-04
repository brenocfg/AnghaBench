#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int n; TYPE_2__* layers; } ;
typedef  TYPE_1__ network ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 scalar_t__ CONVOLUTIONAL ; 
 int gpu_index ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rescale_weights (TYPE_2__,int,double) ; 
 int /*<<< orphan*/  save_weights (TYPE_1__*,char*) ; 

void rescale_net(char *cfgfile, char *weightfile, char *outfile)
{
    gpu_index = -1;
    network *net = load_network(cfgfile, weightfile, 0);
    int i;
    for(i = 0; i < net->n; ++i){
        layer l = net->layers[i];
        if(l.type == CONVOLUTIONAL){
            rescale_weights(l, 2, -.5);
            break;
        }
    }
    save_weights(net, outfile);
}