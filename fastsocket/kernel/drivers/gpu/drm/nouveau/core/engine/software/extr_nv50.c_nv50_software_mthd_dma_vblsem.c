#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int ctxdma; } ;
struct TYPE_6__ {TYPE_1__ vblank; } ;
struct nv50_software_chan {TYPE_2__ base; } ;
struct nouveau_object {int /*<<< orphan*/  parent; } ;
struct nouveau_handle {int /*<<< orphan*/  object; } ;
struct nouveau_gpuobj {TYPE_3__* node; } ;
struct nouveau_fifo_chan {int dummy; } ;
struct TYPE_8__ {scalar_t__ parent; } ;
struct TYPE_7__ {int offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  NV_GPUOBJ_CLASS ; 
 struct nouveau_handle* nouveau_namedb_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_namedb_put (struct nouveau_handle*) ; 
 scalar_t__ nv_engctx (int /*<<< orphan*/ ) ; 
 struct nouveau_gpuobj* nv_gpuobj (int /*<<< orphan*/ ) ; 
 scalar_t__ nv_iclass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_namedb (struct nouveau_fifo_chan*) ; 
 TYPE_4__* nv_object (struct nv50_software_chan*) ; 

__attribute__((used)) static int
nv50_software_mthd_dma_vblsem(struct nouveau_object *object, u32 mthd,
			      void *args, u32 size)
{
	struct nv50_software_chan *chan = (void *)nv_engctx(object->parent);
	struct nouveau_fifo_chan *fifo = (void *)nv_object(chan)->parent;
	struct nouveau_handle *handle;
	int ret = -EINVAL;

	handle = nouveau_namedb_get(nv_namedb(fifo), *(u32 *)args);
	if (!handle)
		return -ENOENT;

	if (nv_iclass(handle->object, NV_GPUOBJ_CLASS)) {
		struct nouveau_gpuobj *gpuobj = nv_gpuobj(handle->object);
		chan->base.vblank.ctxdma = gpuobj->node->offset >> 4;
		ret = 0;
	}
	nouveau_namedb_put(handle);
	return ret;
}