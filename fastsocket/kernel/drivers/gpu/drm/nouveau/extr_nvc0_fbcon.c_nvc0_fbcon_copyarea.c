#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nouveau_fbdev {int /*<<< orphan*/  dev; } ;
struct nouveau_drm {struct nouveau_channel* channel; } ;
struct nouveau_channel {int dummy; } ;
struct fb_info {struct nouveau_fbdev* par; } ;
struct fb_copyarea {int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NVC0 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int /*<<< orphan*/  NvSub2D ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int /*<<< orphan*/ ) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 

int
nvc0_fbcon_copyarea(struct fb_info *info, const struct fb_copyarea *region)
{
	struct nouveau_fbdev *nfbdev = info->par;
	struct nouveau_drm *drm = nouveau_drm(nfbdev->dev);
	struct nouveau_channel *chan = drm->channel;
	int ret;

	ret = RING_SPACE(chan, 12);
	if (ret)
		return ret;

	BEGIN_NVC0(chan, NvSub2D, 0x0110, 1);
	OUT_RING  (chan, 0);
	BEGIN_NVC0(chan, NvSub2D, 0x08b0, 4);
	OUT_RING  (chan, region->dx);
	OUT_RING  (chan, region->dy);
	OUT_RING  (chan, region->width);
	OUT_RING  (chan, region->height);
	BEGIN_NVC0(chan, NvSub2D, 0x08d0, 4);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, region->sx);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, region->sy);
	FIRE_RING(chan);
	return 0;
}