#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct radeon_mode_info {TYPE_4__* atom_context; } ;
struct radeon_encoder_int_tmds {TYPE_3__* tmds_pll; } ;
struct TYPE_5__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_1__ base; } ;
struct radeon_device {struct radeon_mode_info mode_info; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct _ATOM_TMDS_INFO {TYPE_2__* asMiscInfo; int /*<<< orphan*/  usMaxFrequency; } ;
struct TYPE_8__ {int bios; } ;
struct TYPE_7__ {int freq; int value; } ;
struct TYPE_6__ {int ucPLL_ChargePump; int ucPLL_VCO_Gain; int ucPLL_DutyCycle; int ucPLL_VoltageSwing; int /*<<< orphan*/  usFrequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMDS_Info ; 
 scalar_t__ atom_parse_data_header (TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

bool radeon_atombios_get_tmds_info(struct radeon_encoder *encoder,
				   struct radeon_encoder_int_tmds *tmds)
{
	struct drm_device *dev = encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, TMDS_Info);
	uint16_t data_offset;
	struct _ATOM_TMDS_INFO *tmds_info;
	uint8_t frev, crev;
	uint16_t maxfreq;
	int i;

	if (atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		tmds_info =
			(struct _ATOM_TMDS_INFO *)(mode_info->atom_context->bios +
						   data_offset);

		maxfreq = le16_to_cpu(tmds_info->usMaxFrequency);
		for (i = 0; i < 4; i++) {
			tmds->tmds_pll[i].freq =
			    le16_to_cpu(tmds_info->asMiscInfo[i].usFrequency);
			tmds->tmds_pll[i].value =
			    tmds_info->asMiscInfo[i].ucPLL_ChargePump & 0x3f;
			tmds->tmds_pll[i].value |=
			    (tmds_info->asMiscInfo[i].
			     ucPLL_VCO_Gain & 0x3f) << 6;
			tmds->tmds_pll[i].value |=
			    (tmds_info->asMiscInfo[i].
			     ucPLL_DutyCycle & 0xf) << 12;
			tmds->tmds_pll[i].value |=
			    (tmds_info->asMiscInfo[i].
			     ucPLL_VoltageSwing & 0xf) << 16;

			DRM_DEBUG_KMS("TMDS PLL From ATOMBIOS %u %x\n",
				  tmds->tmds_pll[i].freq,
				  tmds->tmds_pll[i].value);

			if (maxfreq == tmds->tmds_pll[i].freq) {
				tmds->tmds_pll[i].freq = 0xffffffff;
				break;
			}
		}
		return true;
	}
	return false;
}