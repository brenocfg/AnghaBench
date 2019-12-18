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
struct nouveau_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int pci_device; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  NV_PBUS_DEBUG_DUALHEAD_CTL ; 
 int /*<<< orphan*/  NV_PCRTC_GPIO_EXT ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void nv04_dfp_update_backlight(struct drm_encoder *encoder, int mode)
{
#ifdef __powerpc__
	struct drm_device *dev = encoder->dev;
	struct nouveau_device *device = nouveau_dev(dev);

	/* BIOS scripts usually take care of the backlight, thanks
	 * Apple for your consistency.
	 */
	if (dev->pci_device == 0x0174 || dev->pci_device == 0x0179 ||
	    dev->pci_device == 0x0189 || dev->pci_device == 0x0329) {
		if (mode == DRM_MODE_DPMS_ON) {
			nv_mask(device, NV_PBUS_DEBUG_DUALHEAD_CTL, 0, 1 << 31);
			nv_mask(device, NV_PCRTC_GPIO_EXT, 3, 1);
		} else {
			nv_mask(device, NV_PBUS_DEBUG_DUALHEAD_CTL, 1 << 31, 0);
			nv_mask(device, NV_PCRTC_GPIO_EXT, 3, 0);
		}
	}
#endif
}