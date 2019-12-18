#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct radeon_encoder_primary_dac {int ps2_pdac_adj; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_1__ base; } ;
struct radeon_device {int dummy; } ;
struct drm_device {TYPE_2__* pdev; struct radeon_device* dev_private; } ;
struct TYPE_4__ {int device; int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBIOS_CRT_INFO_TABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RBIOS8 (scalar_t__) ; 
 scalar_t__ combios_get_table_offset (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct radeon_encoder_primary_dac* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_legacy_get_primary_dac_info_from_table (struct radeon_device*,struct radeon_encoder_primary_dac*) ; 

struct radeon_encoder_primary_dac *radeon_combios_get_primary_dac_info(struct
								       radeon_encoder
								       *encoder)
{
	struct drm_device *dev = encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	uint16_t dac_info;
	uint8_t rev, bg, dac;
	struct radeon_encoder_primary_dac *p_dac = NULL;
	int found = 0;

	p_dac = kzalloc(sizeof(struct radeon_encoder_primary_dac),
			GFP_KERNEL);

	if (!p_dac)
		return NULL;

	/* check CRT table */
	dac_info = combios_get_table_offset(dev, COMBIOS_CRT_INFO_TABLE);
	if (dac_info) {
		rev = RBIOS8(dac_info) & 0x3;
		if (rev < 2) {
			bg = RBIOS8(dac_info + 0x2) & 0xf;
			dac = (RBIOS8(dac_info + 0x2) >> 4) & 0xf;
			p_dac->ps2_pdac_adj = (bg << 8) | (dac);
		} else {
			bg = RBIOS8(dac_info + 0x2) & 0xf;
			dac = RBIOS8(dac_info + 0x3) & 0xf;
			p_dac->ps2_pdac_adj = (bg << 8) | (dac);
		}
		/* if the values are all zeros, use the table */
		if (p_dac->ps2_pdac_adj)
			found = 1;
	}

	/* quirks */
	/* Radeon 9100 (R200) */
	if ((dev->pdev->device == 0x514D) &&
	    (dev->pdev->subsystem_vendor == 0x174B) &&
	    (dev->pdev->subsystem_device == 0x7149)) {
		/* vbios value is bad, use the default */
		found = 0;
	}

	if (!found) /* fallback to defaults */
		radeon_legacy_get_primary_dac_info_from_table(rdev, p_dac);

	return p_dac;
}