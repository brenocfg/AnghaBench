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
struct TYPE_2__ {int uevent; int /*<<< orphan*/  waiting; int /*<<< orphan*/  context_del; int /*<<< orphan*/  context_new; int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; int /*<<< orphan*/  (* dtor ) (struct nouveau_drm*) ;} ;
struct nv84_fence_priv {int /*<<< orphan*/  bo_gart; int /*<<< orphan*/  bo; TYPE_1__ base; } ;
struct nouveau_fifo {int max; } ;
struct nouveau_drm {int /*<<< orphan*/  dev; struct nv84_fence_priv* fence; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TTM_PL_FLAG_TT ; 
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct nv84_fence_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nouveau_bo_map (int /*<<< orphan*/ ) ; 
 int nouveau_bo_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nouveau_bo_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (int /*<<< orphan*/ ) ; 
 struct nouveau_fifo* nouveau_fifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv84_fence_context_del ; 
 int /*<<< orphan*/  nv84_fence_context_new ; 
 int /*<<< orphan*/  nv84_fence_destroy (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nv84_fence_resume ; 
 int /*<<< orphan*/  nv84_fence_suspend ; 

int
nv84_fence_create(struct nouveau_drm *drm)
{
	struct nouveau_fifo *pfifo = nouveau_fifo(drm->device);
	struct nv84_fence_priv *priv;
	int ret;

	priv = drm->fence = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->base.dtor = nv84_fence_destroy;
	priv->base.suspend = nv84_fence_suspend;
	priv->base.resume = nv84_fence_resume;
	priv->base.context_new = nv84_fence_context_new;
	priv->base.context_del = nv84_fence_context_del;

	init_waitqueue_head(&priv->base.waiting);
	priv->base.uevent = true;

	ret = nouveau_bo_new(drm->dev, 16 * (pfifo->max + 1), 0,
			     TTM_PL_FLAG_VRAM, 0, 0, NULL, &priv->bo);
	if (ret == 0) {
		ret = nouveau_bo_pin(priv->bo, TTM_PL_FLAG_VRAM);
		if (ret == 0) {
			ret = nouveau_bo_map(priv->bo);
			if (ret)
				nouveau_bo_unpin(priv->bo);
		}
		if (ret)
			nouveau_bo_ref(NULL, &priv->bo);
	}

	if (ret == 0)
		ret = nouveau_bo_new(drm->dev, 16 * (pfifo->max + 1), 0,
				     TTM_PL_FLAG_TT, 0, 0, NULL,
				     &priv->bo_gart);
	if (ret == 0) {
		ret = nouveau_bo_pin(priv->bo_gart, TTM_PL_FLAG_TT);
		if (ret == 0) {
			ret = nouveau_bo_map(priv->bo_gart);
			if (ret)
				nouveau_bo_unpin(priv->bo_gart);
		}
		if (ret)
			nouveau_bo_ref(NULL, &priv->bo_gart);
	}

	if (ret)
		nv84_fence_destroy(drm);
	return ret;
}