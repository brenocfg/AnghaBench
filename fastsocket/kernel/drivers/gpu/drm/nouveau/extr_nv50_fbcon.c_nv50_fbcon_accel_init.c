#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nouveau_object {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  offset; } ;
struct nouveau_framebuffer {TYPE_4__ vma; } ;
struct nouveau_fbdev {struct drm_device* dev; struct nouveau_framebuffer nouveau_fb; } ;
struct nouveau_drm {struct nouveau_channel* channel; } ;
struct nouveau_channel {int /*<<< orphan*/  cli; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;
struct TYPE_7__ {int bits_per_pixel; int xres_virtual; int yres_virtual; TYPE_1__ transp; } ;
struct TYPE_6__ {int line_length; } ;
struct fb_info {TYPE_3__ var; TYPE_2__ fix; struct nouveau_fbdev* par; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NVDRM_CHAN ; 
 int Nv2D ; 
 int NvDmaFB ; 
 int /*<<< orphan*/  NvSub2D ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_fbcon_gpu_lockup (struct fb_info*) ; 
 int nouveau_object_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nouveau_object**) ; 
 int /*<<< orphan*/  nv_object (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

int
nv50_fbcon_accel_init(struct fb_info *info)
{
	struct nouveau_fbdev *nfbdev = info->par;
	struct nouveau_framebuffer *fb = &nfbdev->nouveau_fb;
	struct drm_device *dev = nfbdev->dev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_channel *chan = drm->channel;
	struct nouveau_object *object;
	int ret, format;

	switch (info->var.bits_per_pixel) {
	case 8:
		format = 0xf3;
		break;
	case 15:
		format = 0xf8;
		break;
	case 16:
		format = 0xe8;
		break;
	case 32:
		switch (info->var.transp.length) {
		case 0: /* depth 24 */
		case 8: /* depth 32, just use 24.. */
			format = 0xe6;
			break;
		case 2: /* depth 30 */
			format = 0xd1;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	ret = nouveau_object_new(nv_object(chan->cli), NVDRM_CHAN, Nv2D,
				 0x502d, NULL, 0, &object);
	if (ret)
		return ret;

	ret = RING_SPACE(chan, 59);
	if (ret) {
		nouveau_fbcon_gpu_lockup(info);
		return ret;
	}

	BEGIN_NV04(chan, NvSub2D, 0x0000, 1);
	OUT_RING(chan, Nv2D);
	BEGIN_NV04(chan, NvSub2D, 0x0184, 3);
	OUT_RING(chan, NvDmaFB);
	OUT_RING(chan, NvDmaFB);
	OUT_RING(chan, NvDmaFB);
	BEGIN_NV04(chan, NvSub2D, 0x0290, 1);
	OUT_RING(chan, 0);
	BEGIN_NV04(chan, NvSub2D, 0x0888, 1);
	OUT_RING(chan, 1);
	BEGIN_NV04(chan, NvSub2D, 0x02ac, 1);
	OUT_RING(chan, 3);
	BEGIN_NV04(chan, NvSub2D, 0x02a0, 1);
	OUT_RING(chan, 0x55);
	BEGIN_NV04(chan, NvSub2D, 0x08c0, 4);
	OUT_RING(chan, 0);
	OUT_RING(chan, 1);
	OUT_RING(chan, 0);
	OUT_RING(chan, 1);
	BEGIN_NV04(chan, NvSub2D, 0x0580, 2);
	OUT_RING(chan, 4);
	OUT_RING(chan, format);
	BEGIN_NV04(chan, NvSub2D, 0x02e8, 2);
	OUT_RING(chan, 2);
	OUT_RING(chan, 1);
	BEGIN_NV04(chan, NvSub2D, 0x0804, 1);
	OUT_RING(chan, format);
	BEGIN_NV04(chan, NvSub2D, 0x0800, 1);
	OUT_RING(chan, 1);
	BEGIN_NV04(chan, NvSub2D, 0x0808, 3);
	OUT_RING(chan, 0);
	OUT_RING(chan, 0);
	OUT_RING(chan, 1);
	BEGIN_NV04(chan, NvSub2D, 0x081c, 1);
	OUT_RING(chan, 1);
	BEGIN_NV04(chan, NvSub2D, 0x0840, 4);
	OUT_RING(chan, 0);
	OUT_RING(chan, 1);
	OUT_RING(chan, 0);
	OUT_RING(chan, 1);
	BEGIN_NV04(chan, NvSub2D, 0x0200, 2);
	OUT_RING(chan, format);
	OUT_RING(chan, 1);
	BEGIN_NV04(chan, NvSub2D, 0x0214, 5);
	OUT_RING(chan, info->fix.line_length);
	OUT_RING(chan, info->var.xres_virtual);
	OUT_RING(chan, info->var.yres_virtual);
	OUT_RING(chan, upper_32_bits(fb->vma.offset));
	OUT_RING(chan, lower_32_bits(fb->vma.offset));
	BEGIN_NV04(chan, NvSub2D, 0x0230, 2);
	OUT_RING(chan, format);
	OUT_RING(chan, 1);
	BEGIN_NV04(chan, NvSub2D, 0x0244, 5);
	OUT_RING(chan, info->fix.line_length);
	OUT_RING(chan, info->var.xres_virtual);
	OUT_RING(chan, info->var.yres_virtual);
	OUT_RING(chan, upper_32_bits(fb->vma.offset));
	OUT_RING(chan, lower_32_bits(fb->vma.offset));

	return 0;
}