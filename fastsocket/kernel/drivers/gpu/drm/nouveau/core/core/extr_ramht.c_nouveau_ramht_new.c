#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_ramht {int /*<<< orphan*/  bits; } ;
struct nouveau_object {struct nouveau_object* engine; } ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVOBJ_FLAG_ZERO_ALLOC ; 
 int /*<<< orphan*/  log2i (int) ; 
 int nouveau_gpuobj_create (struct nouveau_object*,struct nouveau_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nouveau_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nouveau_ramht**) ; 
 int /*<<< orphan*/  nouveau_ramht_oclass ; 
 TYPE_1__* nv_gpuobj (struct nouveau_ramht*) ; 

int
nouveau_ramht_new(struct nouveau_object *parent, struct nouveau_object *pargpu,
		  u32 size, u32 align, struct nouveau_ramht **pramht)
{
	struct nouveau_ramht *ramht;
	int ret;

	ret = nouveau_gpuobj_create(parent, parent->engine ?
				    parent->engine : parent, /* <nv50 ramht */
				    &nouveau_ramht_oclass, 0, pargpu, size,
				    align, NVOBJ_FLAG_ZERO_ALLOC, &ramht);
	*pramht = ramht;
	if (ret)
		return ret;

	ramht->bits = log2i(nv_gpuobj(ramht)->size >> 3);
	return 0;
}