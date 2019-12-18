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
typedef  int uint32_t ;
struct nouveau_drm {int /*<<< orphan*/  device; struct drm_device* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* show ) (struct nouveau_crtc*,int) ;int /*<<< orphan*/  offset; int /*<<< orphan*/  (* set_offset ) (struct nouveau_crtc*,int /*<<< orphan*/ ) ;TYPE_4__* nvbo; int /*<<< orphan*/  (* hide ) (struct nouveau_crtc*,int) ;} ;
struct nouveau_crtc {TYPE_2__ cursor; } ;
struct nouveau_bo {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {TYPE_1__ bo; } ;
struct TYPE_8__ {int chipset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_device*,struct drm_file*,int) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (struct drm_gem_object*) ; 
 int nouveau_bo_map (struct nouveau_bo*) ; 
 int /*<<< orphan*/  nouveau_bo_unmap (struct nouveau_bo*) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 struct nouveau_bo* nouveau_gem_object (struct drm_gem_object*) ; 
 int /*<<< orphan*/  nv04_cursor_upload (struct drm_device*,struct nouveau_bo*,TYPE_4__*) ; 
 int /*<<< orphan*/  nv11_cursor_upload (struct drm_device*,struct nouveau_bo*,TYPE_4__*) ; 
 TYPE_3__* nv_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_crtc*,int) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct nouveau_crtc*,int) ; 

__attribute__((used)) static int
nv04_crtc_cursor_set(struct drm_crtc *crtc, struct drm_file *file_priv,
		     uint32_t buffer_handle, uint32_t width, uint32_t height)
{
	struct nouveau_drm *drm = nouveau_drm(crtc->dev);
	struct drm_device *dev = drm->dev;
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct nouveau_bo *cursor = NULL;
	struct drm_gem_object *gem;
	int ret = 0;

	if (!buffer_handle) {
		nv_crtc->cursor.hide(nv_crtc, true);
		return 0;
	}

	if (width != 64 || height != 64)
		return -EINVAL;

	gem = drm_gem_object_lookup(dev, file_priv, buffer_handle);
	if (!gem)
		return -ENOENT;
	cursor = nouveau_gem_object(gem);

	ret = nouveau_bo_map(cursor);
	if (ret)
		goto out;

	if (nv_device(drm->device)->chipset >= 0x11)
		nv11_cursor_upload(dev, cursor, nv_crtc->cursor.nvbo);
	else
		nv04_cursor_upload(dev, cursor, nv_crtc->cursor.nvbo);

	nouveau_bo_unmap(cursor);
	nv_crtc->cursor.offset = nv_crtc->cursor.nvbo->bo.offset;
	nv_crtc->cursor.set_offset(nv_crtc, nv_crtc->cursor.offset);
	nv_crtc->cursor.show(nv_crtc, true);
out:
	drm_gem_object_unreference_unlocked(gem);
	return ret;
}