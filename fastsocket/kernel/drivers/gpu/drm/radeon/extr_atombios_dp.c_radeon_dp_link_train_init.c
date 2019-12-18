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
typedef  int u8 ;
struct radeon_encoder_atom_dig {scalar_t__ panel_mode; } ;
struct radeon_encoder {struct radeon_encoder_atom_dig* enc_priv; } ;
struct radeon_dp_link_train_info {int* dpcd; int dp_lane_count; int /*<<< orphan*/  radeon_connector; int /*<<< orphan*/  enc_id; int /*<<< orphan*/  dp_clock; int /*<<< orphan*/  rdev; int /*<<< orphan*/  encoder; int /*<<< orphan*/  use_dpencoder; TYPE_1__* connector; } ;
struct TYPE_2__ {scalar_t__ connector_type; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATOM_DP_ACTION_TRAINING_START ; 
 int /*<<< orphan*/  ATOM_ENCODER_CMD_DP_LINK_TRAINING_START ; 
 int /*<<< orphan*/  DP_DOWNSPREAD_CTRL ; 
 size_t DP_DPCD_REV ; 
 int /*<<< orphan*/  DP_EDP_CONFIGURATION_SET ; 
 int DP_ENHANCED_FRAME_CAP ; 
 int DP_LANE_COUNT_ENHANCED_FRAME_EN ; 
 int /*<<< orphan*/  DP_LANE_COUNT_SET ; 
 int /*<<< orphan*/  DP_LINK_BW_SET ; 
 size_t DP_MAX_LANE_COUNT ; 
 scalar_t__ DP_PANEL_MODE_INTERNAL_DP2_MODE ; 
 int /*<<< orphan*/  DP_SET_POWER ; 
 int DP_SET_POWER_D0 ; 
 int DP_SPREAD_AMP_0_5 ; 
 int DP_TRAINING_PATTERN_DISABLE ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_SET ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 int /*<<< orphan*/  atombios_dig_encoder_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_dp_link_rate_to_bw_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_dp_encoder_service (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_write_dpcd_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct radeon_encoder* to_radeon_encoder (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radeon_dp_link_train_init(struct radeon_dp_link_train_info *dp_info)
{
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(dp_info->encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	u8 tmp;

	/* power up the sink */
	if (dp_info->dpcd[0] >= 0x11)
		radeon_write_dpcd_reg(dp_info->radeon_connector,
				      DP_SET_POWER, DP_SET_POWER_D0);

	/* possibly enable downspread on the sink */
	if (dp_info->dpcd[3] & 0x1)
		radeon_write_dpcd_reg(dp_info->radeon_connector,
				      DP_DOWNSPREAD_CTRL, DP_SPREAD_AMP_0_5);
	else
		radeon_write_dpcd_reg(dp_info->radeon_connector,
				      DP_DOWNSPREAD_CTRL, 0);

	if ((dp_info->connector->connector_type == DRM_MODE_CONNECTOR_eDP) &&
	    (dig->panel_mode == DP_PANEL_MODE_INTERNAL_DP2_MODE)) {
		radeon_write_dpcd_reg(dp_info->radeon_connector, DP_EDP_CONFIGURATION_SET, 1);
	}

	/* set the lane count on the sink */
	tmp = dp_info->dp_lane_count;
	if (dp_info->dpcd[DP_DPCD_REV] >= 0x11 &&
	    dp_info->dpcd[DP_MAX_LANE_COUNT] & DP_ENHANCED_FRAME_CAP)
		tmp |= DP_LANE_COUNT_ENHANCED_FRAME_EN;
	radeon_write_dpcd_reg(dp_info->radeon_connector, DP_LANE_COUNT_SET, tmp);

	/* set the link rate on the sink */
	tmp = drm_dp_link_rate_to_bw_code(dp_info->dp_clock);
	radeon_write_dpcd_reg(dp_info->radeon_connector, DP_LINK_BW_SET, tmp);

	/* start training on the source */
	if (ASIC_IS_DCE4(dp_info->rdev) || !dp_info->use_dpencoder)
		atombios_dig_encoder_setup(dp_info->encoder,
					   ATOM_ENCODER_CMD_DP_LINK_TRAINING_START, 0);
	else
		radeon_dp_encoder_service(dp_info->rdev, ATOM_DP_ACTION_TRAINING_START,
					  dp_info->dp_clock, dp_info->enc_id, 0);

	/* disable the training pattern on the sink */
	radeon_write_dpcd_reg(dp_info->radeon_connector,
			      DP_TRAINING_PATTERN_SET,
			      DP_TRAINING_PATTERN_DISABLE);

	return 0;
}