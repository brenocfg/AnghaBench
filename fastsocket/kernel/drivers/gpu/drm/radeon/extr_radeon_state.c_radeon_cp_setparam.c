#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_radeon_master_private {TYPE_2__* sarea_priv; } ;
struct drm_radeon_driver_file_fields {int radeon_fb_delta; } ;
struct drm_file {struct drm_radeon_driver_file_fields* driver_priv; TYPE_1__* master; } ;
struct drm_device {TYPE_5__* dev_private; } ;
struct TYPE_9__ {int param; int value; } ;
typedef  TYPE_4__ drm_radeon_setparam_t ;
struct TYPE_8__ {int table_size; } ;
struct TYPE_10__ {int fb_location; int pcigart_offset; int pcigart_offset_set; int new_memmap; TYPE_3__ gart_info; int /*<<< orphan*/  back_pitch_offset; int /*<<< orphan*/  front_pitch_offset; } ;
typedef  TYPE_5__ drm_radeon_private_t ;
struct TYPE_7__ {int tiling_enabled; } ;
struct TYPE_6__ {struct drm_radeon_master_private* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  RADEON_DST_TILE_MACRO ; 
 int RADEON_PCIGART_TABLE_SIZE ; 
#define  RADEON_SETPARAM_FB_LOCATION 133 
#define  RADEON_SETPARAM_NEW_MEMMAP 132 
#define  RADEON_SETPARAM_PCIGART_LOCATION 131 
#define  RADEON_SETPARAM_PCIGART_TABLE_SIZE 130 
#define  RADEON_SETPARAM_SWITCH_TILING 129 
#define  RADEON_SETPARAM_VBLANK_CRTC 128 
 int radeon_vblank_crtc_set (struct drm_device*,int) ; 

__attribute__((used)) static int radeon_cp_setparam(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	struct drm_radeon_master_private *master_priv = file_priv->master->driver_priv;
	drm_radeon_setparam_t *sp = data;
	struct drm_radeon_driver_file_fields *radeon_priv;

	switch (sp->param) {
	case RADEON_SETPARAM_FB_LOCATION:
		radeon_priv = file_priv->driver_priv;
		radeon_priv->radeon_fb_delta = dev_priv->fb_location -
		    sp->value;
		break;
	case RADEON_SETPARAM_SWITCH_TILING:
		if (sp->value == 0) {
			DRM_DEBUG("color tiling disabled\n");
			dev_priv->front_pitch_offset &= ~RADEON_DST_TILE_MACRO;
			dev_priv->back_pitch_offset &= ~RADEON_DST_TILE_MACRO;
			if (master_priv->sarea_priv)
				master_priv->sarea_priv->tiling_enabled = 0;
		} else if (sp->value == 1) {
			DRM_DEBUG("color tiling enabled\n");
			dev_priv->front_pitch_offset |= RADEON_DST_TILE_MACRO;
			dev_priv->back_pitch_offset |= RADEON_DST_TILE_MACRO;
			if (master_priv->sarea_priv)
				master_priv->sarea_priv->tiling_enabled = 1;
		}
		break;
	case RADEON_SETPARAM_PCIGART_LOCATION:
		dev_priv->pcigart_offset = sp->value;
		dev_priv->pcigart_offset_set = 1;
		break;
	case RADEON_SETPARAM_NEW_MEMMAP:
		dev_priv->new_memmap = sp->value;
		break;
	case RADEON_SETPARAM_PCIGART_TABLE_SIZE:
		dev_priv->gart_info.table_size = sp->value;
		if (dev_priv->gart_info.table_size < RADEON_PCIGART_TABLE_SIZE)
			dev_priv->gart_info.table_size = RADEON_PCIGART_TABLE_SIZE;
		break;
	case RADEON_SETPARAM_VBLANK_CRTC:
		return radeon_vblank_crtc_set(dev, sp->value);
		break;
	default:
		DRM_DEBUG("Invalid parameter %d\n", sp->param);
		return -EINVAL;
	}

	return 0;
}