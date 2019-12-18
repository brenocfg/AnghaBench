#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  base; } ;
struct TYPE_11__ {int /*<<< orphan*/  base; } ;
struct TYPE_10__ {int /*<<< orphan*/  base; } ;
struct TYPE_9__ {int /*<<< orphan*/  base; } ;
struct nv50_head {TYPE_4__ curs; TYPE_3__ sync; TYPE_2__ oimm; TYPE_1__ ovly; } ;
struct nv50_disp {int /*<<< orphan*/  core; } ;
struct nouveau_event {int /*<<< orphan*/  lock; } ;
struct TYPE_15__ {scalar_t__ nvbo; } ;
struct TYPE_14__ {scalar_t__ nvbo; } ;
struct TYPE_13__ {int /*<<< orphan*/  head; } ;
struct nouveau_crtc {TYPE_7__ lut; TYPE_6__ cursor; TYPE_5__ vblank; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct TYPE_16__ {struct nouveau_event* vblank; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_cleanup (struct drm_crtc*) ; 
 int /*<<< orphan*/  kfree (struct drm_crtc*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nouveau_bo_unmap (scalar_t__) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (scalar_t__) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  nouveau_dev (int /*<<< orphan*/ ) ; 
 TYPE_8__* nouveau_disp (int /*<<< orphan*/ ) ; 
 struct nv50_disp* nv50_disp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_dmac_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nv50_head* nv50_head (struct drm_crtc*) ; 
 int /*<<< orphan*/  nv50_pioc_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
nv50_crtc_destroy(struct drm_crtc *crtc)
{
	struct nouveau_event *event = nouveau_disp(nouveau_dev(crtc->dev))->vblank;
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct nv50_disp *disp = nv50_disp(crtc->dev);
	struct nv50_head *head = nv50_head(crtc);
	unsigned long flags;

	nv50_dmac_destroy(disp->core, &head->ovly.base);
	nv50_pioc_destroy(disp->core, &head->oimm.base);
	nv50_dmac_destroy(disp->core, &head->sync.base);
	nv50_pioc_destroy(disp->core, &head->curs.base);

	spin_lock_irqsave(&event->lock, flags);
	list_del(&nv_crtc->vblank.head);
	spin_unlock_irqrestore(&event->lock, flags);

	nouveau_bo_unmap(nv_crtc->cursor.nvbo);
	if (nv_crtc->cursor.nvbo)
		nouveau_bo_unpin(nv_crtc->cursor.nvbo);
	nouveau_bo_ref(NULL, &nv_crtc->cursor.nvbo);
	nouveau_bo_unmap(nv_crtc->lut.nvbo);
	if (nv_crtc->lut.nvbo)
		nouveau_bo_unpin(nv_crtc->lut.nvbo);
	nouveau_bo_ref(NULL, &nv_crtc->lut.nvbo);
	drm_crtc_cleanup(crtc);
	kfree(crtc);
}