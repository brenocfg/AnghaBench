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
struct TYPE_5__ {int n; TYPE_2__* layers; } ;
typedef  TYPE_1__ network ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_2__ layer ;
typedef  int /*<<< orphan*/  image ;

/* Variables and functions */
 scalar_t__ CONVOLUTIONAL ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/ * visualize_convolutional_layer (TYPE_2__,char*,int /*<<< orphan*/ *) ; 

void visualize_network(network *net)
{
    image *prev = 0;
    int i;
    char buff[256];
    for(i = 0; i < net->n; ++i){
        sprintf(buff, "Layer %d", i);
        layer l = net->layers[i];
        if(l.type == CONVOLUTIONAL){
            prev = visualize_convolutional_layer(l, buff, prev);
        }
    } 
}