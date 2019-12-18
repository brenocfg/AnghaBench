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
typedef  int uint32_t ;
struct nouveau_fbdev {int /*<<< orphan*/  dev; } ;
struct nouveau_drm {struct nouveau_channel* channel; } ;
struct nouveau_channel {int dummy; } ;
struct TYPE_4__ {scalar_t__ visual; } ;
struct TYPE_3__ {int bits_per_pixel; } ;
struct fb_info {int* pseudo_palette; TYPE_2__ fix; TYPE_1__ var; struct nouveau_fbdev* par; } ;
struct fb_image {int depth; int width; int height; size_t bg_color; size_t fg_color; int dx; int dy; scalar_t__ data; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  BEGIN_NIC0 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BEGIN_NVC0 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int ENODEV ; 
 scalar_t__ FB_VISUAL_DIRECTCOLOR ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int /*<<< orphan*/  NvSub2D ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int /*<<< orphan*/  OUT_RINGp (struct nouveau_channel*,int*,int) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 

int
nvc0_fbcon_imageblit(struct fb_info *info, const struct fb_image *image)
{
	struct nouveau_fbdev *nfbdev = info->par;
	struct nouveau_drm *drm = nouveau_drm(nfbdev->dev);
	struct nouveau_channel *chan = drm->channel;
	uint32_t width, dwords, *data = (uint32_t *)image->data;
	uint32_t mask = ~(~0 >> (32 - info->var.bits_per_pixel));
	uint32_t *palette = info->pseudo_palette;
	int ret;

	if (image->depth != 1)
		return -ENODEV;

	ret = RING_SPACE(chan, 11);
	if (ret)
		return ret;

	width = ALIGN(image->width, 32);
	dwords = (width * image->height) >> 5;

	BEGIN_NVC0(chan, NvSub2D, 0x0814, 2);
	if (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	    info->fix.visual == FB_VISUAL_DIRECTCOLOR) {
		OUT_RING  (chan, palette[image->bg_color] | mask);
		OUT_RING  (chan, palette[image->fg_color] | mask);
	} else {
		OUT_RING  (chan, image->bg_color);
		OUT_RING  (chan, image->fg_color);
	}
	BEGIN_NVC0(chan, NvSub2D, 0x0838, 2);
	OUT_RING  (chan, image->width);
	OUT_RING  (chan, image->height);
	BEGIN_NVC0(chan, NvSub2D, 0x0850, 4);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, image->dx);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, image->dy);

	while (dwords) {
		int push = dwords > 2047 ? 2047 : dwords;

		ret = RING_SPACE(chan, push + 1);
		if (ret)
			return ret;

		dwords -= push;

		BEGIN_NIC0(chan, NvSub2D, 0x0860, push);
		OUT_RINGp(chan, data, push);
		data += push;
	}

	FIRE_RING(chan);
	return 0;
}