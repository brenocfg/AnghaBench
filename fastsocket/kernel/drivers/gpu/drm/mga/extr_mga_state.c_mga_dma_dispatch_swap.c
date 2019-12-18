#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_device {TYPE_4__* dev_private; } ;
struct drm_clip_rect {int y2; int y1; int x1; int x2; } ;
struct TYPE_6__ {int /*<<< orphan*/  wrap; int /*<<< orphan*/  head; } ;
struct TYPE_10__ {int plnwt; int dwgctl; } ;
struct TYPE_8__ {int nbox; TYPE_1__ last_frame; struct drm_clip_rect* boxes; TYPE_5__ context_state; } ;
typedef  TYPE_3__ drm_mga_sarea_t ;
struct TYPE_7__ {int /*<<< orphan*/  last_wrap; int /*<<< orphan*/  tail; } ;
struct TYPE_9__ {int front_offset; int maccess; int back_offset; int front_pitch; TYPE_2__ prim; TYPE_3__* sarea_priv; } ;
typedef  TYPE_4__ drm_mga_private_t ;
typedef  TYPE_5__ drm_mga_context_regs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_DMA () ; 
 int /*<<< orphan*/  BEGIN_DMA (int) ; 
 int /*<<< orphan*/  DMA_BLOCK (scalar_t__,int,scalar_t__,int,scalar_t__,int,scalar_t__,int) ; 
 int /*<<< orphan*/  DMA_LOCALS ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  FLUSH_DMA () ; 
 scalar_t__ MGA_AR0 ; 
 scalar_t__ MGA_AR3 ; 
 scalar_t__ MGA_AR5 ; 
 scalar_t__ MGA_DMAPAD ; 
 scalar_t__ MGA_DSTORG ; 
 scalar_t__ MGA_DWGCTL ; 
 int MGA_DWGCTL_COPY ; 
 scalar_t__ MGA_DWGSYNC ; 
 scalar_t__ MGA_EXEC ; 
 scalar_t__ MGA_FXBNDRY ; 
 scalar_t__ MGA_MACCESS ; 
 scalar_t__ MGA_PLNWT ; 
 scalar_t__ MGA_SRCORG ; 
 scalar_t__ MGA_YDSTLEN ; 

__attribute__((used)) static void mga_dma_dispatch_swap(struct drm_device *dev)
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	struct drm_clip_rect *pbox = sarea_priv->boxes;
	int nbox = sarea_priv->nbox;
	int i;
	DMA_LOCALS;
	DRM_DEBUG("\n");

	sarea_priv->last_frame.head = dev_priv->prim.tail;
	sarea_priv->last_frame.wrap = dev_priv->prim.last_wrap;

	BEGIN_DMA(4 + nbox);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DWGSYNC, 0x00007100, MGA_DWGSYNC, 0x00007000);

	DMA_BLOCK(MGA_DSTORG, dev_priv->front_offset,
		  MGA_MACCESS, dev_priv->maccess,
		  MGA_SRCORG, dev_priv->back_offset,
		  MGA_AR5, dev_priv->front_pitch);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_PLNWT, 0xffffffff, MGA_DWGCTL, MGA_DWGCTL_COPY);

	for (i = 0; i < nbox; i++) {
		struct drm_clip_rect *box = &pbox[i];
		u32 height = box->y2 - box->y1;
		u32 start = box->y1 * dev_priv->front_pitch;

		DRM_DEBUG("   from=%d,%d to=%d,%d\n",
			  box->x1, box->y1, box->x2, box->y2);

		DMA_BLOCK(MGA_AR0, start + box->x2 - 1,
			  MGA_AR3, start + box->x1,
			  MGA_FXBNDRY, ((box->x2 - 1) << 16) | box->x1,
			  MGA_YDSTLEN + MGA_EXEC, (box->y1 << 16) | height);
	}

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_PLNWT, ctx->plnwt,
		  MGA_SRCORG, dev_priv->front_offset, MGA_DWGCTL, ctx->dwgctl);

	ADVANCE_DMA();

	FLUSH_DMA();

	DRM_DEBUG("... done.\n");
}