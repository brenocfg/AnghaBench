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
struct radeon_mode_info {TYPE_2__* atom_context; } ;
struct radeon_encoder_primary_dac {int ps2_pdac_adj; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_1__ base; } ;
struct radeon_device {struct radeon_mode_info mode_info; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct _COMPASSIONATE_DATA {int ucDAC1_BG_Adjustment; int ucDAC1_DAC_Adjustment; } ;
struct TYPE_4__ {scalar_t__ bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  CompassionateData ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atom_parse_data_header (TYPE_2__*,int,int /*<<< orphan*/ *,int*,int*,scalar_t__*) ; 
 struct radeon_encoder_primary_dac* kzalloc (int,int /*<<< orphan*/ ) ; 

struct radeon_encoder_primary_dac *
radeon_atombios_get_primary_dac_info(struct radeon_encoder *encoder)
{
	struct drm_device *dev = encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, CompassionateData);
	uint16_t data_offset;
	struct _COMPASSIONATE_DATA *dac_info;
	uint8_t frev, crev;
	uint8_t bg, dac;
	struct radeon_encoder_primary_dac *p_dac = NULL;

	if (atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		dac_info = (struct _COMPASSIONATE_DATA *)
			(mode_info->atom_context->bios + data_offset);

		p_dac = kzalloc(sizeof(struct radeon_encoder_primary_dac), GFP_KERNEL);

		if (!p_dac)
			return NULL;

		bg = dac_info->ucDAC1_BG_Adjustment;
		dac = dac_info->ucDAC1_DAC_Adjustment;
		p_dac->ps2_pdac_adj = (bg << 8) | (dac);

	}
	return p_dac;
}