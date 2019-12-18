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
struct TYPE_5__ {scalar_t__ delta; } ;
typedef  TYPE_1__ network ;
struct TYPE_6__ {int outputs; int batch; int w; int h; int inputs; int /*<<< orphan*/  stride; int /*<<< orphan*/  c; scalar_t__ delta; scalar_t__ extra; scalar_t__ reverse; scalar_t__ flatten; } ;
typedef  TYPE_2__ layer ;

/* Variables and functions */
 int /*<<< orphan*/  copy_cpu (int,scalar_t__,int,scalar_t__,int) ; 
 int /*<<< orphan*/  flatten (scalar_t__,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  reorg_cpu (scalar_t__,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,scalar_t__) ; 

void backward_reorg_layer(const layer l, network net)
{
    int i;
    if(l.flatten){
        memcpy(net.delta, l.delta, l.outputs*l.batch*sizeof(float));
        if(l.reverse){
            flatten(net.delta, l.w*l.h, l.c, l.batch, 1);
        }else{
            flatten(net.delta, l.w*l.h, l.c, l.batch, 0);
        }
    } else if(l.reverse){
        reorg_cpu(l.delta, l.w, l.h, l.c, l.batch, l.stride, 0, net.delta);
    } else if (l.extra) {
        for(i = 0; i < l.batch; ++i){
            copy_cpu(l.inputs, l.delta + i*l.outputs, 1, net.delta + i*l.inputs, 1);
        }
    }else{
        reorg_cpu(l.delta, l.w, l.h, l.c, l.batch, l.stride, 1, net.delta);
    }
}