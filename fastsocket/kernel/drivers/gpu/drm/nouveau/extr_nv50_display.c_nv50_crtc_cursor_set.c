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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int visible; int /*<<< orphan*/  nvbo; } ;
struct nouveau_crtc {TYPE_1__ cursor; } ;
struct nouveau_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_device*,struct drm_file*,int) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (struct drm_gem_object*) ; 
 int nouveau_bo_map (struct nouveau_bo*) ; 
 int /*<<< orphan*/  nouveau_bo_rd32 (struct nouveau_bo*,int) ; 
 int /*<<< orphan*/  nouveau_bo_unmap (struct nouveau_bo*) ; 
 int /*<<< orphan*/  nouveau_bo_wr32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 struct nouveau_bo* nouveau_gem_object (struct drm_gem_object*) ; 
 int /*<<< orphan*/  nv50_crtc_cursor_show_hide (struct nouveau_crtc*,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
nv50_crtc_cursor_set(struct drm_crtc *crtc, struct drm_file *file_priv,
		     uint32_t handle, uint32_t width, uint32_t height)
{
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct drm_gem_object *gem;
	struct nouveau_bo *nvbo;
	bool visible = (handle != 0);
	int i, ret = 0;

	if (visible) {
		if (width != 64 || height != 64)
			return -EINVAL;

		gem = drm_gem_object_lookup(dev, file_priv, handle);
		if (unlikely(!gem))
			return -ENOENT;
		nvbo = nouveau_gem_object(gem);

		ret = nouveau_bo_map(nvbo);
		if (ret == 0) {
			for (i = 0; i < 64 * 64; i++) {
				u32 v = nouveau_bo_rd32(nvbo, i);
				nouveau_bo_wr32(nv_crtc->cursor.nvbo, i, v);
			}
			nouveau_bo_unmap(nvbo);
		}

		drm_gem_object_unreference_unlocked(gem);
	}

	if (visible != nv_crtc->cursor.visible) {
		nv50_crtc_cursor_show_hide(nv_crtc, visible, true);
		nv_crtc->cursor.visible = visible;
	}

	return ret;
}