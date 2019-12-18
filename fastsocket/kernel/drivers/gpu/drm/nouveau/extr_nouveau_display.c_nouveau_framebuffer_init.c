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
typedef  int u32 ;
struct drm_framebuffer {int depth; int* pitches; } ;
struct nouveau_framebuffer {int r_format; int r_pitch; int /*<<< orphan*/  r_dma; struct nouveau_bo* nvbo; struct drm_framebuffer base; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_bo {int tile_mode; } ;
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ card_type; int chipset; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NV_50 ; 
 scalar_t__ NV_C0 ; 
 scalar_t__ NV_D0 ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,int) ; 
 int /*<<< orphan*/  NvEvoFB16 ; 
 int /*<<< orphan*/  NvEvoFB32 ; 
 int /*<<< orphan*/  NvEvoVRAM_LP ; 
 int drm_framebuffer_init (struct drm_device*,struct drm_framebuffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_framebuffer*,struct drm_mode_fb_cmd2*) ; 
 int nouveau_bo_tile_layout (struct nouveau_bo*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_framebuffer_funcs ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 

int
nouveau_framebuffer_init(struct drm_device *dev,
			 struct nouveau_framebuffer *nv_fb,
			 struct drm_mode_fb_cmd2 *mode_cmd,
			 struct nouveau_bo *nvbo)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct drm_framebuffer *fb = &nv_fb->base;
	int ret;

	drm_helper_mode_fill_fb_struct(fb, mode_cmd);
	nv_fb->nvbo = nvbo;

	if (nv_device(drm->device)->card_type >= NV_50) {
		u32 tile_flags = nouveau_bo_tile_layout(nvbo);
		if (tile_flags == 0x7a00 ||
		    tile_flags == 0xfe00)
			nv_fb->r_dma = NvEvoFB32;
		else
		if (tile_flags == 0x7000)
			nv_fb->r_dma = NvEvoFB16;
		else
			nv_fb->r_dma = NvEvoVRAM_LP;

		switch (fb->depth) {
		case  8: nv_fb->r_format = 0x1e00; break;
		case 15: nv_fb->r_format = 0xe900; break;
		case 16: nv_fb->r_format = 0xe800; break;
		case 24:
		case 32: nv_fb->r_format = 0xcf00; break;
		case 30: nv_fb->r_format = 0xd100; break;
		default:
			 NV_ERROR(drm, "unknown depth %d\n", fb->depth);
			 return -EINVAL;
		}

		if (nv_device(drm->device)->chipset == 0x50)
			nv_fb->r_format |= (tile_flags << 8);

		if (!tile_flags) {
			if (nv_device(drm->device)->card_type < NV_D0)
				nv_fb->r_pitch = 0x00100000 | fb->pitches[0];
			else
				nv_fb->r_pitch = 0x01000000 | fb->pitches[0];
		} else {
			u32 mode = nvbo->tile_mode;
			if (nv_device(drm->device)->card_type >= NV_C0)
				mode >>= 4;
			nv_fb->r_pitch = ((fb->pitches[0] / 4) << 4) | mode;
		}
	}

	ret = drm_framebuffer_init(dev, fb, &nouveau_framebuffer_funcs);
	if (ret) {
		return ret;
	}

	return 0;
}