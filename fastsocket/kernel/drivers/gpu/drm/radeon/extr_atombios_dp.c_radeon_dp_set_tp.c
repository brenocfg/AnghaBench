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
struct radeon_dp_link_train_info {int /*<<< orphan*/  radeon_connector; int /*<<< orphan*/  enc_id; int /*<<< orphan*/  dp_clock; int /*<<< orphan*/  rdev; int /*<<< orphan*/  encoder; int /*<<< orphan*/  use_dpencoder; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATOM_DP_ACTION_TRAINING_PATTERN_SEL ; 
 int ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN1 ; 
 int ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN2 ; 
 int ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN3 ; 
#define  DP_TRAINING_PATTERN_1 130 
#define  DP_TRAINING_PATTERN_2 129 
#define  DP_TRAINING_PATTERN_3 128 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_SET ; 
 int /*<<< orphan*/  atombios_dig_encoder_setup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_dp_encoder_service (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_write_dpcd_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void radeon_dp_set_tp(struct radeon_dp_link_train_info *dp_info, int tp)
{
	int rtp = 0;

	/* set training pattern on the source */
	if (ASIC_IS_DCE4(dp_info->rdev) || !dp_info->use_dpencoder) {
		switch (tp) {
		case DP_TRAINING_PATTERN_1:
			rtp = ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN1;
			break;
		case DP_TRAINING_PATTERN_2:
			rtp = ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN2;
			break;
		case DP_TRAINING_PATTERN_3:
			rtp = ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN3;
			break;
		}
		atombios_dig_encoder_setup(dp_info->encoder, rtp, 0);
	} else {
		switch (tp) {
		case DP_TRAINING_PATTERN_1:
			rtp = 0;
			break;
		case DP_TRAINING_PATTERN_2:
			rtp = 1;
			break;
		}
		radeon_dp_encoder_service(dp_info->rdev, ATOM_DP_ACTION_TRAINING_PATTERN_SEL,
					  dp_info->dp_clock, dp_info->enc_id, rtp);
	}

	/* enable training pattern on the sink */
	radeon_write_dpcd_reg(dp_info->radeon_connector, DP_TRAINING_PATTERN_SET, tp);
}