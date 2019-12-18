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
typedef  int /*<<< orphan*/  u32 ;
struct nv50_disp_priv {int dummy; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int /*<<< orphan*/  refcount; } ;
struct nouveau_engctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  contexts; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NVOBJ_FLAG_HEAP ; 
 scalar_t__ NV_DEVICE_CLASS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nouveau_engctx_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,struct nouveau_engctx**) ; 
 TYPE_2__* nv_engine (struct nv50_disp_priv*) ; 
 scalar_t__ nv_mclass (struct nouveau_object*) ; 
 struct nouveau_object* nv_object (struct nouveau_engctx*) ; 
 TYPE_1__* nv_subdev (struct nv50_disp_priv*) ; 

__attribute__((used)) static int
nv50_disp_data_ctor(struct nouveau_object *parent,
		    struct nouveau_object *engine,
		    struct nouveau_oclass *oclass, void *data, u32 size,
		    struct nouveau_object **pobject)
{
	struct nv50_disp_priv *priv = (void *)engine;
	struct nouveau_engctx *ectx;
	int ret = -EBUSY;

	/* no context needed for channel objects... */
	if (nv_mclass(parent) != NV_DEVICE_CLASS) {
		atomic_inc(&parent->refcount);
		*pobject = parent;
		return 0;
	}

	/* allocate display hardware to client */
	mutex_lock(&nv_subdev(priv)->mutex);
	if (list_empty(&nv_engine(priv)->contexts)) {
		ret = nouveau_engctx_create(parent, engine, oclass, NULL,
					    0x10000, 0x10000,
					    NVOBJ_FLAG_HEAP, &ectx);
		*pobject = nv_object(ectx);
	}
	mutex_unlock(&nv_subdev(priv)->mutex);
	return ret;
}