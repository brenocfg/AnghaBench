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
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_bo {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 int nouveau_bo_rd32 (struct nouveau_bo*,int) ; 
 int /*<<< orphan*/  nouveau_bo_wr32 (struct nouveau_bo*,int,int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nv11_cursor_upload(struct drm_device *dev, struct nouveau_bo *src,
			       struct nouveau_bo *dst)
{
	uint32_t pixel;
	int alpha, i;

	/* nv11+ supports premultiplied (PM), or non-premultiplied (NPM) alpha
	 * cursors (though NPM in combination with fp dithering may not work on
	 * nv11, from "nv" driver history)
	 * NPM mode needs NV_PCRTC_CURSOR_CONFIG_ALPHA_BLEND set and is what the
	 * blob uses, however we get given PM cursors so we use PM mode
	 */
	for (i = 0; i < 64 * 64; i++) {
		pixel = nouveau_bo_rd32(src, i);

		/* hw gets unhappy if alpha <= rgb values.  for a PM image "less
		 * than" shouldn't happen; fix "equal to" case by adding one to
		 * alpha channel (slightly inaccurate, but so is attempting to
		 * get back to NPM images, due to limits of integer precision)
		 */
		alpha = pixel >> 24;
		if (alpha > 0 && alpha < 255)
			pixel = (pixel & 0x00ffffff) | ((alpha + 1) << 24);

#ifdef __BIG_ENDIAN
		{
			struct nouveau_drm *drm = nouveau_drm(dev);

			if (nv_device(drm->device)->chipset == 0x11) {
				pixel = ((pixel & 0x000000ff) << 24) |
					((pixel & 0x0000ff00) << 8) |
					((pixel & 0x00ff0000) >> 8) |
					((pixel & 0xff000000) >> 24);
			}
		}
#endif

		nouveau_bo_wr32(dst, i, pixel);
	}
}