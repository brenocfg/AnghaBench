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
struct nouveau_page_flip_state {int /*<<< orphan*/  head; } ;
struct nouveau_fence_chan {int /*<<< orphan*/  flip; } ;
struct nouveau_fence {int dummy; } ;
struct nouveau_drm {int /*<<< orphan*/  device; struct drm_device* dev; } ;
struct nouveau_channel {struct nouveau_drm* drm; struct nouveau_fence_chan* fence; } ;
struct TYPE_3__ {int /*<<< orphan*/  sync_obj; } ;
struct nouveau_bo {TYPE_1__ bo; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct TYPE_4__ {scalar_t__ card_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_IMC0 (struct nouveau_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BEGIN_NVC0 (struct nouveau_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int /*<<< orphan*/  NV10_SUBCHAN_REF_CNT ; 
 int /*<<< orphan*/  NVSW_SUBCHAN_PAGE_FLIP ; 
 scalar_t__ NV_C0 ; 
 int /*<<< orphan*/  NV_SW_PAGE_FLIP ; 
 int /*<<< orphan*/  NvSubSw ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int nouveau_fence_new (struct nouveau_channel*,int,struct nouveau_fence**) ; 
 int nouveau_fence_sync (int /*<<< orphan*/ ,struct nouveau_channel*) ; 
 TYPE_2__* nv_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
nouveau_page_flip_emit(struct nouveau_channel *chan,
		       struct nouveau_bo *old_bo,
		       struct nouveau_bo *new_bo,
		       struct nouveau_page_flip_state *s,
		       struct nouveau_fence **pfence)
{
	struct nouveau_fence_chan *fctx = chan->fence;
	struct nouveau_drm *drm = chan->drm;
	struct drm_device *dev = drm->dev;
	unsigned long flags;
	int ret;

	/* Queue it to the pending list */
	spin_lock_irqsave(&dev->event_lock, flags);
	list_add_tail(&s->head, &fctx->flip);
	spin_unlock_irqrestore(&dev->event_lock, flags);

	/* Synchronize with the old framebuffer */
	ret = nouveau_fence_sync(old_bo->bo.sync_obj, chan);
	if (ret)
		goto fail;

	/* Emit the pageflip */
	ret = RING_SPACE(chan, 3);
	if (ret)
		goto fail;

	if (nv_device(drm->device)->card_type < NV_C0) {
		BEGIN_NV04(chan, NvSubSw, NV_SW_PAGE_FLIP, 1);
		OUT_RING  (chan, 0x00000000);
		OUT_RING  (chan, 0x00000000);
	} else {
		BEGIN_NVC0(chan, 0, NV10_SUBCHAN_REF_CNT, 1);
		OUT_RING  (chan, 0);
		BEGIN_IMC0(chan, 0, NVSW_SUBCHAN_PAGE_FLIP, 0x0000);
	}
	FIRE_RING (chan);

	ret = nouveau_fence_new(chan, false, pfence);
	if (ret)
		goto fail;

	return 0;
fail:
	spin_lock_irqsave(&dev->event_lock, flags);
	list_del(&s->head);
	spin_unlock_irqrestore(&dev->event_lock, flags);
	return ret;
}