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
typedef  int uint32_t ;
struct nouveau_fbdev {int /*<<< orphan*/  dev; } ;
struct nouveau_drm {struct nouveau_channel* channel; } ;
struct nouveau_channel {int dummy; } ;
struct TYPE_2__ {scalar_t__ visual; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_1__ fix; struct nouveau_fbdev* par; } ;
struct fb_fillrect {scalar_t__ rop; size_t color; int dx; int dy; int width; int height; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ FB_VISUAL_DIRECTCOLOR ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int /*<<< orphan*/  NvSubGdiRect ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 scalar_t__ ROP_COPY ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 

int
nv04_fbcon_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	struct nouveau_fbdev *nfbdev = info->par;
	struct nouveau_drm *drm = nouveau_drm(nfbdev->dev);
	struct nouveau_channel *chan = drm->channel;
	int ret;

	ret = RING_SPACE(chan, 7);
	if (ret)
		return ret;

	BEGIN_NV04(chan, NvSubGdiRect, 0x02fc, 1);
	OUT_RING(chan, (rect->rop != ROP_COPY) ? 1 : 3);
	BEGIN_NV04(chan, NvSubGdiRect, 0x03fc, 1);
	if (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	    info->fix.visual == FB_VISUAL_DIRECTCOLOR)
		OUT_RING(chan, ((uint32_t *)info->pseudo_palette)[rect->color]);
	else
		OUT_RING(chan, rect->color);
	BEGIN_NV04(chan, NvSubGdiRect, 0x0400, 2);
	OUT_RING(chan, (rect->dx << 16) | rect->dy);
	OUT_RING(chan, (rect->width << 16) | rect->height);
	FIRE_RING(chan);
	return 0;
}