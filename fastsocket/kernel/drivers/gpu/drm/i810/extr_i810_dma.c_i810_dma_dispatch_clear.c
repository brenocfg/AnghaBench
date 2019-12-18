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
struct drm_device {TYPE_2__* dev_private; } ;
struct drm_clip_rect {unsigned int x1; unsigned int y1; unsigned int x2; unsigned int y2; } ;
struct TYPE_3__ {int nbox; struct drm_clip_rect* boxes; } ;
typedef  TYPE_1__ drm_i810_sarea_t ;
struct TYPE_4__ {int pitch; int current_page; unsigned int w; unsigned int h; unsigned int back_offset; unsigned int depth_offset; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_i810_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_LP_RING () ; 
 int /*<<< orphan*/  BEGIN_LP_RING (int) ; 
 int BR00_BITBLT_CLIENT ; 
 int BR00_OP_COLOR_BLT ; 
 int BR13_SOLID_PATTERN ; 
 int I810_BACK ; 
 int I810_DEPTH ; 
 int I810_FRONT ; 
 int I810_NR_SAREA_CLIPRECTS ; 
 int /*<<< orphan*/  OUT_RING (unsigned int) ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  i810_kernel_lost_context (struct drm_device*) ; 

__attribute__((used)) static void i810_dma_dispatch_clear(struct drm_device *dev, int flags,
				    unsigned int clear_color,
				    unsigned int clear_zval)
{
	drm_i810_private_t *dev_priv = dev->dev_private;
	drm_i810_sarea_t *sarea_priv = dev_priv->sarea_priv;
	int nbox = sarea_priv->nbox;
	struct drm_clip_rect *pbox = sarea_priv->boxes;
	int pitch = dev_priv->pitch;
	int cpp = 2;
	int i;
	RING_LOCALS;

	if (dev_priv->current_page == 1) {
		unsigned int tmp = flags;

		flags &= ~(I810_FRONT | I810_BACK);
		if (tmp & I810_FRONT)
			flags |= I810_BACK;
		if (tmp & I810_BACK)
			flags |= I810_FRONT;
	}

	i810_kernel_lost_context(dev);

	if (nbox > I810_NR_SAREA_CLIPRECTS)
		nbox = I810_NR_SAREA_CLIPRECTS;

	for (i = 0; i < nbox; i++, pbox++) {
		unsigned int x = pbox->x1;
		unsigned int y = pbox->y1;
		unsigned int width = (pbox->x2 - x) * cpp;
		unsigned int height = pbox->y2 - y;
		unsigned int start = y * pitch + x * cpp;

		if (pbox->x1 > pbox->x2 ||
		    pbox->y1 > pbox->y2 ||
		    pbox->x2 > dev_priv->w || pbox->y2 > dev_priv->h)
			continue;

		if (flags & I810_FRONT) {
			BEGIN_LP_RING(6);
			OUT_RING(BR00_BITBLT_CLIENT | BR00_OP_COLOR_BLT | 0x3);
			OUT_RING(BR13_SOLID_PATTERN | (0xF0 << 16) | pitch);
			OUT_RING((height << 16) | width);
			OUT_RING(start);
			OUT_RING(clear_color);
			OUT_RING(0);
			ADVANCE_LP_RING();
		}

		if (flags & I810_BACK) {
			BEGIN_LP_RING(6);
			OUT_RING(BR00_BITBLT_CLIENT | BR00_OP_COLOR_BLT | 0x3);
			OUT_RING(BR13_SOLID_PATTERN | (0xF0 << 16) | pitch);
			OUT_RING((height << 16) | width);
			OUT_RING(dev_priv->back_offset + start);
			OUT_RING(clear_color);
			OUT_RING(0);
			ADVANCE_LP_RING();
		}

		if (flags & I810_DEPTH) {
			BEGIN_LP_RING(6);
			OUT_RING(BR00_BITBLT_CLIENT | BR00_OP_COLOR_BLT | 0x3);
			OUT_RING(BR13_SOLID_PATTERN | (0xF0 << 16) | pitch);
			OUT_RING((height << 16) | width);
			OUT_RING(dev_priv->depth_offset + start);
			OUT_RING(clear_zval);
			OUT_RING(0);
			ADVANCE_LP_RING();
		}
	}
}