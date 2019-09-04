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
struct TYPE_7__ {int n; TYPE_2__* layers; } ;
typedef  TYPE_1__ network ;
struct TYPE_8__ {scalar_t__ type; scalar_t__ batch_normalize; struct TYPE_8__* state_h_layer; struct TYPE_8__* state_r_layer; struct TYPE_8__* state_z_layer; struct TYPE_8__* input_h_layer; struct TYPE_8__* input_r_layer; struct TYPE_8__* input_z_layer; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 scalar_t__ CONNECTED ; 
 scalar_t__ CONVOLUTIONAL ; 
 scalar_t__ DECONVOLUTIONAL ; 
 scalar_t__ GRU ; 
 int /*<<< orphan*/  denormalize_connected_layer (TYPE_2__) ; 
 int /*<<< orphan*/  denormalize_convolutional_layer (TYPE_2__) ; 
 int gpu_index ; 
 TYPE_1__* load_network (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_weights (TYPE_1__*,char*) ; 

void denormalize_net(char *cfgfile, char *weightfile, char *outfile)
{
    gpu_index = -1;
    network *net = load_network(cfgfile, weightfile, 0);
    int i;
    for (i = 0; i < net->n; ++i) {
        layer l = net->layers[i];
        if ((l.type == DECONVOLUTIONAL || l.type == CONVOLUTIONAL) && l.batch_normalize) {
            denormalize_convolutional_layer(l);
            net->layers[i].batch_normalize=0;
        }
        if (l.type == CONNECTED && l.batch_normalize) {
            denormalize_connected_layer(l);
            net->layers[i].batch_normalize=0;
        }
        if (l.type == GRU && l.batch_normalize) {
            denormalize_connected_layer(*l.input_z_layer);
            denormalize_connected_layer(*l.input_r_layer);
            denormalize_connected_layer(*l.input_h_layer);
            denormalize_connected_layer(*l.state_z_layer);
            denormalize_connected_layer(*l.state_r_layer);
            denormalize_connected_layer(*l.state_h_layer);
            l.input_z_layer->batch_normalize = 0;
            l.input_r_layer->batch_normalize = 0;
            l.input_h_layer->batch_normalize = 0;
            l.state_z_layer->batch_normalize = 0;
            l.state_r_layer->batch_normalize = 0;
            l.state_h_layer->batch_normalize = 0;
            net->layers[i].batch_normalize=0;
        }
    }
    save_weights(net, outfile);
}