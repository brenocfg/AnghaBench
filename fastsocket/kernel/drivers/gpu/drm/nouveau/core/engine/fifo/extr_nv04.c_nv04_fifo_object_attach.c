#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nv04_fifo_priv {int /*<<< orphan*/  ramht; } ;
struct TYPE_4__ {int chid; } ;
struct nv04_fifo_chan {TYPE_1__ base; } ;
struct nouveau_object {scalar_t__ engine; } ;
struct TYPE_6__ {int addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVDEV_ENGINE_DMAOBJ 131 
#define  NVDEV_ENGINE_GR 130 
#define  NVDEV_ENGINE_MPEG 129 
#define  NVDEV_ENGINE_SW 128 
 int /*<<< orphan*/  NV_GPUOBJ_CLASS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nouveau_ramht_insert (int /*<<< orphan*/ ,int,int,int) ; 
 int nv_engidx (scalar_t__) ; 
 TYPE_3__* nv_gpuobj (struct nouveau_object*) ; 
 scalar_t__ nv_iclass (struct nouveau_object*,int /*<<< orphan*/ ) ; 
 TYPE_2__* nv_subdev (struct nv04_fifo_priv*) ; 

int
nv04_fifo_object_attach(struct nouveau_object *parent,
			struct nouveau_object *object, u32 handle)
{
	struct nv04_fifo_priv *priv = (void *)parent->engine;
	struct nv04_fifo_chan *chan = (void *)parent;
	u32 context, chid = chan->base.chid;
	int ret;

	if (nv_iclass(object, NV_GPUOBJ_CLASS))
		context = nv_gpuobj(object)->addr >> 4;
	else
		context = 0x00000004; /* just non-zero */

	switch (nv_engidx(object->engine)) {
	case NVDEV_ENGINE_DMAOBJ:
	case NVDEV_ENGINE_SW:
		context |= 0x00000000;
		break;
	case NVDEV_ENGINE_GR:
		context |= 0x00010000;
		break;
	case NVDEV_ENGINE_MPEG:
		context |= 0x00020000;
		break;
	default:
		return -EINVAL;
	}

	context |= 0x80000000; /* valid */
	context |= chid << 24;

	mutex_lock(&nv_subdev(priv)->mutex);
	ret = nouveau_ramht_insert(priv->ramht, chid, handle, context);
	mutex_unlock(&nv_subdev(priv)->mutex);
	return ret;
}