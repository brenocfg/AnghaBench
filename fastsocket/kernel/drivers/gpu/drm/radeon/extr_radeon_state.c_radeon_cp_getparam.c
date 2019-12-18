#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {TYPE_3__* dev_private; } ;
struct TYPE_7__ {int /*<<< orphan*/  last_clear_reads; int /*<<< orphan*/  last_frame_reads; } ;
struct TYPE_9__ {int gart_buffers_offset; int flags; int gart_vm_start; int ring_rptr_offset; int gart_textures_offset; int num_gb_pipes; int num_z_pipes; int /*<<< orphan*/  writeback_works; TYPE_2__* mmio; TYPE_1__ stats; } ;
typedef  TYPE_3__ drm_radeon_private_t ;
struct TYPE_10__ {int param; int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ drm_radeon_getparam_t ;
struct TYPE_8__ {int offset; } ;

/* Variables and functions */
 int CHIP_R600 ; 
 scalar_t__ DRM_COPY_TO_USER (int /*<<< orphan*/ ,int*,int) ; 
 int DRM_CURRENTPID ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EFAULT ; 
 int EINVAL ; 
 int GET_SCRATCH (TYPE_3__*,int) ; 
 int R600_SCRATCH_REG_OFFSET ; 
 int RADEON_CARD_AGP ; 
 int RADEON_CARD_PCI ; 
 int RADEON_CARD_PCIE ; 
 int RADEON_FAMILY_MASK ; 
 int RADEON_IS_AGP ; 
 int RADEON_IS_PCIE ; 
#define  RADEON_PARAM_CARD_TYPE 143 
#define  RADEON_PARAM_FB_LOCATION 142 
#define  RADEON_PARAM_GART_BASE 141 
#define  RADEON_PARAM_GART_BUFFER_OFFSET 140 
#define  RADEON_PARAM_GART_TEX_HANDLE 139 
#define  RADEON_PARAM_IRQ_NR 138 
#define  RADEON_PARAM_LAST_CLEAR 137 
#define  RADEON_PARAM_LAST_DISPATCH 136 
#define  RADEON_PARAM_LAST_FRAME 135 
#define  RADEON_PARAM_NUM_GB_PIPES 134 
#define  RADEON_PARAM_NUM_Z_PIPES 133 
#define  RADEON_PARAM_REGISTER_HANDLE 132 
#define  RADEON_PARAM_SAREA_HANDLE 131 
#define  RADEON_PARAM_SCRATCH_OFFSET 130 
#define  RADEON_PARAM_STATUS_HANDLE 129 
#define  RADEON_PARAM_VBLANK_CRTC 128 
 int RADEON_SCRATCH_REG_OFFSET ; 
 int drm_dev_to_irq (struct drm_device*) ; 
 int radeon_read_fb_location (TYPE_3__*) ; 
 int radeon_vblank_crtc_get (struct drm_device*) ; 

__attribute__((used)) static int radeon_cp_getparam(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	drm_radeon_getparam_t *param = data;
	int value;

	DRM_DEBUG("pid=%d\n", DRM_CURRENTPID);

	switch (param->param) {
	case RADEON_PARAM_GART_BUFFER_OFFSET:
		value = dev_priv->gart_buffers_offset;
		break;
	case RADEON_PARAM_LAST_FRAME:
		dev_priv->stats.last_frame_reads++;
		value = GET_SCRATCH(dev_priv, 0);
		break;
	case RADEON_PARAM_LAST_DISPATCH:
		value = GET_SCRATCH(dev_priv, 1);
		break;
	case RADEON_PARAM_LAST_CLEAR:
		dev_priv->stats.last_clear_reads++;
		value = GET_SCRATCH(dev_priv, 2);
		break;
	case RADEON_PARAM_IRQ_NR:
		if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
			value = 0;
		else
			value = drm_dev_to_irq(dev);
		break;
	case RADEON_PARAM_GART_BASE:
		value = dev_priv->gart_vm_start;
		break;
	case RADEON_PARAM_REGISTER_HANDLE:
		value = dev_priv->mmio->offset;
		break;
	case RADEON_PARAM_STATUS_HANDLE:
		value = dev_priv->ring_rptr_offset;
		break;
#if BITS_PER_LONG == 32
		/*
		 * This ioctl() doesn't work on 64-bit platforms because hw_lock is a
		 * pointer which can't fit into an int-sized variable.  According to
		 * Michel Dänzer, the ioctl() is only used on embedded platforms, so
		 * not supporting it shouldn't be a problem.  If the same functionality
		 * is needed on 64-bit platforms, a new ioctl() would have to be added,
		 * so backwards-compatibility for the embedded platforms can be
		 * maintained.  --davidm 4-Feb-2004.
		 */
	case RADEON_PARAM_SAREA_HANDLE:
		/* The lock is the first dword in the sarea. */
		/* no users of this parameter */
		break;
#endif
	case RADEON_PARAM_GART_TEX_HANDLE:
		value = dev_priv->gart_textures_offset;
		break;
	case RADEON_PARAM_SCRATCH_OFFSET:
		if (!dev_priv->writeback_works)
			return -EINVAL;
		if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
			value = R600_SCRATCH_REG_OFFSET;
		else
			value = RADEON_SCRATCH_REG_OFFSET;
		break;
	case RADEON_PARAM_CARD_TYPE:
		if (dev_priv->flags & RADEON_IS_PCIE)
			value = RADEON_CARD_PCIE;
		else if (dev_priv->flags & RADEON_IS_AGP)
			value = RADEON_CARD_AGP;
		else
			value = RADEON_CARD_PCI;
		break;
	case RADEON_PARAM_VBLANK_CRTC:
		value = radeon_vblank_crtc_get(dev);
		break;
	case RADEON_PARAM_FB_LOCATION:
		value = radeon_read_fb_location(dev_priv);
		break;
	case RADEON_PARAM_NUM_GB_PIPES:
		value = dev_priv->num_gb_pipes;
		break;
	case RADEON_PARAM_NUM_Z_PIPES:
		value = dev_priv->num_z_pipes;
		break;
	default:
		DRM_DEBUG("Invalid parameter %d\n", param->param);
		return -EINVAL;
	}

	if (DRM_COPY_TO_USER(param->value, &value, sizeof(int))) {
		DRM_ERROR("copy_to_user\n");
		return -EFAULT;
	}

	return 0;
}