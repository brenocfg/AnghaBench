#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_19__ ;
typedef  struct TYPE_29__   TYPE_18__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int n; TYPE_19__* layers; } ;
typedef  TYPE_18__ network ;
struct TYPE_30__ {scalar_t__ type; long n; long size; long c; long groups; long out_h; long out_w; long inputs; long outputs; TYPE_17__* wo; TYPE_16__* wg; TYPE_15__* wi; TYPE_14__* wf; TYPE_13__* uo; TYPE_12__* ug; TYPE_11__* ui; TYPE_10__* uf; TYPE_9__* wr; TYPE_8__* wh; TYPE_7__* wz; TYPE_6__* ur; TYPE_5__* uh; TYPE_4__* uz; TYPE_3__* output_layer; TYPE_2__* self_layer; TYPE_1__* input_layer; } ;
typedef  TYPE_19__ layer ;
struct TYPE_39__ {long inputs; long outputs; } ;
struct TYPE_38__ {long inputs; long outputs; } ;
struct TYPE_37__ {long inputs; long outputs; } ;
struct TYPE_36__ {long inputs; long outputs; } ;
struct TYPE_35__ {long inputs; long outputs; } ;
struct TYPE_34__ {long inputs; long outputs; } ;
struct TYPE_33__ {long inputs; long outputs; } ;
struct TYPE_32__ {long inputs; long outputs; } ;
struct TYPE_31__ {long inputs; long outputs; } ;
struct TYPE_28__ {long inputs; long outputs; } ;
struct TYPE_27__ {long inputs; long outputs; } ;
struct TYPE_26__ {long inputs; long outputs; } ;
struct TYPE_25__ {long inputs; long outputs; } ;
struct TYPE_24__ {long inputs; long outputs; } ;
struct TYPE_23__ {long inputs; long outputs; } ;
struct TYPE_22__ {long inputs; long outputs; } ;
struct TYPE_21__ {long inputs; long outputs; } ;

/* Variables and functions */
 scalar_t__ CONNECTED ; 
 scalar_t__ CONVOLUTIONAL ; 
 scalar_t__ GRU ; 
 scalar_t__ LSTM ; 
 scalar_t__ RNN ; 

long numops(network *net)
{
    int i;
    long ops = 0;
    for(i = 0; i < net->n; ++i){
        layer l = net->layers[i];
        if(l.type == CONVOLUTIONAL){
            ops += 2l * l.n * l.size*l.size*l.c/l.groups * l.out_h*l.out_w;
        } else if(l.type == CONNECTED){
            ops += 2l * l.inputs * l.outputs;
        } else if (l.type == RNN){
            ops += 2l * l.input_layer->inputs * l.input_layer->outputs;
            ops += 2l * l.self_layer->inputs * l.self_layer->outputs;
            ops += 2l * l.output_layer->inputs * l.output_layer->outputs;
        } else if (l.type == GRU){
            ops += 2l * l.uz->inputs * l.uz->outputs;
            ops += 2l * l.uh->inputs * l.uh->outputs;
            ops += 2l * l.ur->inputs * l.ur->outputs;
            ops += 2l * l.wz->inputs * l.wz->outputs;
            ops += 2l * l.wh->inputs * l.wh->outputs;
            ops += 2l * l.wr->inputs * l.wr->outputs;
        } else if (l.type == LSTM){
            ops += 2l * l.uf->inputs * l.uf->outputs;
            ops += 2l * l.ui->inputs * l.ui->outputs;
            ops += 2l * l.ug->inputs * l.ug->outputs;
            ops += 2l * l.uo->inputs * l.uo->outputs;
            ops += 2l * l.wf->inputs * l.wf->outputs;
            ops += 2l * l.wi->inputs * l.wi->outputs;
            ops += 2l * l.wg->inputs * l.wg->outputs;
            ops += 2l * l.wo->inputs * l.wo->outputs;
        }
    }
    return ops;
}