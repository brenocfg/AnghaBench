#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct drm_radeon_driver_file_fields {scalar_t__ radeon_fb_delta; } ;
struct drm_file {struct drm_radeon_driver_file_fields* driver_priv; } ;
struct TYPE_4__ {scalar_t__ fb_location; scalar_t__ fb_size; scalar_t__ gart_size; scalar_t__ gart_vm_start; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned int) ; 
 int EINVAL ; 
 scalar_t__ radeon_check_offset (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static __inline__ int radeon_check_and_fixup_offset(drm_radeon_private_t *
						    dev_priv,
						    struct drm_file * file_priv,
						    u32 *offset)
{
	u64 off = *offset;
	u32 fb_end = dev_priv->fb_location + dev_priv->fb_size - 1;
	struct drm_radeon_driver_file_fields *radeon_priv;

	/* Hrm ... the story of the offset ... So this function converts
	 * the various ideas of what userland clients might have for an
	 * offset in the card address space into an offset into the card
	 * address space :) So with a sane client, it should just keep
	 * the value intact and just do some boundary checking. However,
	 * not all clients are sane. Some older clients pass us 0 based
	 * offsets relative to the start of the framebuffer and some may
	 * assume the AGP aperture it appended to the framebuffer, so we
	 * try to detect those cases and fix them up.
	 *
	 * Note: It might be a good idea here to make sure the offset lands
	 * in some "allowed" area to protect things like the PCIE GART...
	 */

	/* First, the best case, the offset already lands in either the
	 * framebuffer or the GART mapped space
	 */
	if (radeon_check_offset(dev_priv, off))
		return 0;

	/* Ok, that didn't happen... now check if we have a zero based
	 * offset that fits in the framebuffer + gart space, apply the
	 * magic offset we get from SETPARAM or calculated from fb_location
	 */
	if (off < (dev_priv->fb_size + dev_priv->gart_size)) {
		radeon_priv = file_priv->driver_priv;
		off += radeon_priv->radeon_fb_delta;
	}

	/* Finally, assume we aimed at a GART offset if beyond the fb */
	if (off > fb_end)
		off = off - fb_end - 1 + dev_priv->gart_vm_start;

	/* Now recheck and fail if out of bounds */
	if (radeon_check_offset(dev_priv, off)) {
		DRM_DEBUG("offset fixed up to 0x%x\n", (unsigned int)off);
		*offset = off;
		return 0;
	}
	return -EINVAL;
}