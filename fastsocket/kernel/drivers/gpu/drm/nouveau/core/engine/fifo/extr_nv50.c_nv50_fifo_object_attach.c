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
struct nv50_fifo_chan {int /*<<< orphan*/  ramht; } ;
struct nouveau_object {int /*<<< orphan*/  engine; } ;
struct TYPE_4__ {TYPE_1__* node; } ;
struct TYPE_3__ {int offset; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVDEV_ENGINE_DMAOBJ 131 
#define  NVDEV_ENGINE_GR 130 
#define  NVDEV_ENGINE_MPEG 129 
#define  NVDEV_ENGINE_SW 128 
 int /*<<< orphan*/  NV_GPUOBJ_CLASS ; 
 int nouveau_ramht_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int nv_engidx (int /*<<< orphan*/ ) ; 
 TYPE_2__* nv_gpuobj (struct nouveau_object*) ; 
 scalar_t__ nv_iclass (struct nouveau_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv50_fifo_object_attach(struct nouveau_object *parent,
			struct nouveau_object *object, u32 handle)
{
	struct nv50_fifo_chan *chan = (void *)parent;
	u32 context;

	if (nv_iclass(object, NV_GPUOBJ_CLASS))
		context = nv_gpuobj(object)->node->offset >> 4;
	else
		context = 0x00000004; /* just non-zero */

	switch (nv_engidx(object->engine)) {
	case NVDEV_ENGINE_DMAOBJ:
	case NVDEV_ENGINE_SW    : context |= 0x00000000; break;
	case NVDEV_ENGINE_GR    : context |= 0x00100000; break;
	case NVDEV_ENGINE_MPEG  : context |= 0x00200000; break;
	default:
		return -EINVAL;
	}

	return nouveau_ramht_insert(chan->ramht, 0, handle, context);
}