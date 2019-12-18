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
struct radeon_i2c_bus_rec {scalar_t__ mask_clk_reg; } ;
struct radeon_hpd {int dummy; } ;
struct drm_device {TYPE_1__* pdev; } ;
typedef  enum radeon_combios_connector { ____Placeholder_radeon_combios_connector } radeon_combios_connector ;
struct TYPE_2__ {int device; int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 int CONNECTOR_CRT_LEGACY ; 
 int CONNECTOR_DVI_I_LEGACY ; 
 scalar_t__ RADEON_GPIO_CRT2_DDC ; 

__attribute__((used)) static bool radeon_apply_legacy_quirks(struct drm_device *dev,
				       int bios_index,
				       enum radeon_combios_connector
				       *legacy_connector,
				       struct radeon_i2c_bus_rec *ddc_i2c,
				       struct radeon_hpd *hpd)
{

	/* Certain IBM chipset RN50s have a BIOS reporting two VGAs,
	   one with VGA DDC and one with CRT2 DDC. - kill the CRT2 DDC one */
	if (dev->pdev->device == 0x515e &&
	    dev->pdev->subsystem_vendor == 0x1014) {
		if (*legacy_connector == CONNECTOR_CRT_LEGACY &&
		    ddc_i2c->mask_clk_reg == RADEON_GPIO_CRT2_DDC)
			return false;
	}

	/* X300 card with extra non-existent DVI port */
	if (dev->pdev->device == 0x5B60 &&
	    dev->pdev->subsystem_vendor == 0x17af &&
	    dev->pdev->subsystem_device == 0x201e && bios_index == 2) {
		if (*legacy_connector == CONNECTOR_DVI_I_LEGACY)
			return false;
	}

	return true;
}