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
struct TYPE_2__ {int /*<<< orphan*/  context_del; int /*<<< orphan*/  context_new; int /*<<< orphan*/  resume; int /*<<< orphan*/  (* dtor ) (struct nouveau_drm*) ;} ;
struct nv10_fence_priv {int /*<<< orphan*/  bo; int /*<<< orphan*/  lock; TYPE_1__ base; } ;
struct nouveau_drm {int /*<<< orphan*/  dev; struct nv10_fence_priv* fence; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 struct nv10_fence_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nouveau_bo_map (int /*<<< orphan*/ ) ; 
 int nouveau_bo_new (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nouveau_bo_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_bo_wr32 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nv10_fence_context_del ; 
 int /*<<< orphan*/  nv10_fence_destroy (struct nouveau_drm*) ; 
 int /*<<< orphan*/  nv17_fence_context_new ; 
 int /*<<< orphan*/  nv17_fence_resume ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nv17_fence_create(struct nouveau_drm *drm)
{
	struct nv10_fence_priv *priv;
	int ret = 0;

	priv = drm->fence = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->base.dtor = nv10_fence_destroy;
	priv->base.resume = nv17_fence_resume;
	priv->base.context_new = nv17_fence_context_new;
	priv->base.context_del = nv10_fence_context_del;
	spin_lock_init(&priv->lock);

	ret = nouveau_bo_new(drm->dev, 4096, 0x1000, TTM_PL_FLAG_VRAM,
			     0, 0x0000, NULL, &priv->bo);
	if (!ret) {
		ret = nouveau_bo_pin(priv->bo, TTM_PL_FLAG_VRAM);
		if (!ret) {
			ret = nouveau_bo_map(priv->bo);
			if (ret)
				nouveau_bo_unpin(priv->bo);
		}
		if (ret)
			nouveau_bo_ref(NULL, &priv->bo);
	}

	if (ret) {
		nv10_fence_destroy(drm);
		return ret;
	}

	nouveau_bo_wr32(priv->bo, 0x000, 0x00000000);
	return ret;
}