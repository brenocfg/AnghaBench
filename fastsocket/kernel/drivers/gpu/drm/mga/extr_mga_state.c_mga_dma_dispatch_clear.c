#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_device {TYPE_2__* dev_private; } ;
struct drm_clip_rect {int y2; int y1; int x1; int x2; } ;
struct TYPE_8__ {int plnwt; int dwgctl; } ;
struct TYPE_6__ {int nbox; struct drm_clip_rect* boxes; TYPE_3__ context_state; } ;
typedef  TYPE_1__ drm_mga_sarea_t ;
struct TYPE_7__ {int front_offset; int clear_cmd; int back_offset; int depth_offset; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;
typedef  TYPE_3__ drm_mga_context_regs_t ;
struct TYPE_9__ {int flags; int color_mask; int clear_color; int depth_mask; int clear_depth; } ;
typedef  TYPE_4__ drm_mga_clear_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_DMA () ; 
 int /*<<< orphan*/  BEGIN_DMA (int) ; 
 int /*<<< orphan*/  DMA_BLOCK (scalar_t__,int,scalar_t__,int,scalar_t__,int,scalar_t__,int) ; 
 int /*<<< orphan*/  DMA_LOCALS ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  FLUSH_DMA () ; 
 int MGA_BACK ; 
 int MGA_DEPTH ; 
 scalar_t__ MGA_DMAPAD ; 
 scalar_t__ MGA_DSTORG ; 
 scalar_t__ MGA_DWGCTL ; 
 scalar_t__ MGA_DWGSYNC ; 
 scalar_t__ MGA_EXEC ; 
 scalar_t__ MGA_FCOL ; 
 int MGA_FRONT ; 
 scalar_t__ MGA_FXBNDRY ; 
 scalar_t__ MGA_PLNWT ; 
 scalar_t__ MGA_YDSTLEN ; 

__attribute__((used)) static void mga_dma_dispatch_clear(struct drm_device *dev, drm_mga_clear_t *clear)
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_context_regs_t *ctx = &sarea_priv->context_state;
	struct drm_clip_rect *pbox = sarea_priv->boxes;
	int nbox = sarea_priv->nbox;
	int i;
	DMA_LOCALS;
	DRM_DEBUG("\n");

	BEGIN_DMA(1);

	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DWGSYNC, 0x00007100, MGA_DWGSYNC, 0x00007000);

	ADVANCE_DMA();

	for (i = 0; i < nbox; i++) {
		struct drm_clip_rect *box = &pbox[i];
		u32 height = box->y2 - box->y1;

		DRM_DEBUG("   from=%d,%d to=%d,%d\n",
			  box->x1, box->y1, box->x2, box->y2);

		if (clear->flags & MGA_FRONT) {
			BEGIN_DMA(2);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_PLNWT, clear->color_mask,
				  MGA_YDSTLEN, (box->y1 << 16) | height,
				  MGA_FXBNDRY, (box->x2 << 16) | box->x1);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_FCOL, clear->clear_color,
				  MGA_DSTORG, dev_priv->front_offset,
				  MGA_DWGCTL + MGA_EXEC, dev_priv->clear_cmd);

			ADVANCE_DMA();
		}

		if (clear->flags & MGA_BACK) {
			BEGIN_DMA(2);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_PLNWT, clear->color_mask,
				  MGA_YDSTLEN, (box->y1 << 16) | height,
				  MGA_FXBNDRY, (box->x2 << 16) | box->x1);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_FCOL, clear->clear_color,
				  MGA_DSTORG, dev_priv->back_offset,
				  MGA_DWGCTL + MGA_EXEC, dev_priv->clear_cmd);

			ADVANCE_DMA();
		}

		if (clear->flags & MGA_DEPTH) {
			BEGIN_DMA(2);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_PLNWT, clear->depth_mask,
				  MGA_YDSTLEN, (box->y1 << 16) | height,
				  MGA_FXBNDRY, (box->x2 << 16) | box->x1);

			DMA_BLOCK(MGA_DMAPAD, 0x00000000,
				  MGA_FCOL, clear->clear_depth,
				  MGA_DSTORG, dev_priv->depth_offset,
				  MGA_DWGCTL + MGA_EXEC, dev_priv->clear_cmd);

			ADVANCE_DMA();
		}

	}

	BEGIN_DMA(1);

	/* Force reset of DWGCTL */
	DMA_BLOCK(MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000,
		  MGA_PLNWT, ctx->plnwt, MGA_DWGCTL, ctx->dwgctl);

	ADVANCE_DMA();

	FLUSH_DMA();
}