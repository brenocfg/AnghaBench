#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nv50_disp_chan {int chid; } ;
struct nv50_disp_base {int /*<<< orphan*/  ramht; } ;
struct nouveau_object {scalar_t__ parent; } ;
struct TYPE_4__ {TYPE_1__* node; } ;
struct TYPE_3__ {int offset; } ;

/* Variables and functions */
 int nouveau_ramht_insert (int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_2__* nv_gpuobj (struct nouveau_object*) ; 

__attribute__((used)) static int
nv50_disp_dmac_object_attach(struct nouveau_object *parent,
			     struct nouveau_object *object, u32 name)
{
	struct nv50_disp_base *base = (void *)parent->parent;
	struct nv50_disp_chan *chan = (void *)parent;
	u32 addr = nv_gpuobj(object)->node->offset;
	u32 chid = chan->chid;
	u32 data = (chid << 28) | (addr << 10) | chid;
	return nouveau_ramht_insert(base->ramht, chid, name, data);
}