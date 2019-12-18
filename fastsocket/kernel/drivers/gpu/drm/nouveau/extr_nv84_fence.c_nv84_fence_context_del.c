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
struct nv84_fence_priv {struct nouveau_bo* bo; } ;
struct nv84_fence_chan {int /*<<< orphan*/  base; int /*<<< orphan*/  vma; int /*<<< orphan*/  vma_gart; int /*<<< orphan*/ * dispc_vma; } ;
struct nouveau_channel {struct nv84_fence_chan* fence; TYPE_1__* drm; } ;
struct nouveau_bo {int dummy; } ;
struct TYPE_4__ {int num_crtc; } ;
struct drm_device {TYPE_2__ mode_config; } ;
struct TYPE_3__ {struct nv84_fence_priv* fence; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nv84_fence_chan*) ; 
 int /*<<< orphan*/  nouveau_bo_vma_del (struct nouveau_bo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_fence_context_del (int /*<<< orphan*/ *) ; 
 struct nouveau_bo* nv50_display_crtc_sema (struct drm_device*,int) ; 

__attribute__((used)) static void
nv84_fence_context_del(struct nouveau_channel *chan)
{
	struct drm_device *dev = chan->drm->dev;
	struct nv84_fence_priv *priv = chan->drm->fence;
	struct nv84_fence_chan *fctx = chan->fence;
	int i;

	for (i = 0; i < dev->mode_config.num_crtc; i++) {
		struct nouveau_bo *bo = nv50_display_crtc_sema(dev, i);
		nouveau_bo_vma_del(bo, &fctx->dispc_vma[i]);
	}

	nouveau_bo_vma_del(priv->bo, &fctx->vma_gart);
	nouveau_bo_vma_del(priv->bo, &fctx->vma);
	nouveau_fence_context_del(&fctx->base);
	chan->fence = NULL;
	kfree(fctx);
}