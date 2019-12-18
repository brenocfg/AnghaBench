#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int CHIP_RV770 ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  r600_cp_init_ring_buffer (struct drm_device*,TYPE_1__*,struct drm_file*) ; 
 int /*<<< orphan*/  r600_cp_load_microcode (TYPE_1__*) ; 
 int /*<<< orphan*/  r600_do_engine_reset (struct drm_device*) ; 
 int /*<<< orphan*/  r600_vm_init (struct drm_device*) ; 
 int /*<<< orphan*/  r700_cp_load_microcode (TYPE_1__*) ; 
 int /*<<< orphan*/  r700_vm_init (struct drm_device*) ; 

int r600_do_resume_cp(struct drm_device *dev, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;

	DRM_DEBUG("\n");
	if (((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RV770)) {
		r700_vm_init(dev);
		r700_cp_load_microcode(dev_priv);
	} else {
		r600_vm_init(dev);
		r600_cp_load_microcode(dev_priv);
	}
	r600_cp_init_ring_buffer(dev, dev_priv, file_priv);
	r600_do_engine_reset(dev);

	return 0;
}