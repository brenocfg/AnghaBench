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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_ofuncs {int /*<<< orphan*/  (* wr32 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct nouveau_object {int dummy; } ;
struct nouveau_gpuobj {int /*<<< orphan*/  parent; TYPE_1__* node; } ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */
 struct nouveau_gpuobj* nv_gpuobj (struct nouveau_object*) ; 
 struct nouveau_ofuncs* nv_ofuncs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
_nouveau_gpuobj_wr32(struct nouveau_object *object, u64 addr, u32 data)
{
	struct nouveau_gpuobj *gpuobj = nv_gpuobj(object);
	struct nouveau_ofuncs *pfuncs = nv_ofuncs(gpuobj->parent);
	if (gpuobj->node)
		addr += gpuobj->node->offset;
	pfuncs->wr32(gpuobj->parent, addr, data);
}