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
struct radeon_dp_link_train_info {int /*<<< orphan*/  enc_id; int /*<<< orphan*/  dp_clock; int /*<<< orphan*/  rdev; int /*<<< orphan*/  encoder; int /*<<< orphan*/  use_dpencoder; int /*<<< orphan*/  radeon_connector; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATOM_DP_ACTION_TRAINING_COMPLETE ; 
 int /*<<< orphan*/  ATOM_ENCODER_CMD_DP_LINK_TRAINING_COMPLETE ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_DISABLE ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_SET ; 
 int /*<<< orphan*/  atombios_dig_encoder_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_dp_encoder_service (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_write_dpcd_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int radeon_dp_link_train_finish(struct radeon_dp_link_train_info *dp_info)
{
	udelay(400);

	/* disable the training pattern on the sink */
	radeon_write_dpcd_reg(dp_info->radeon_connector,
			      DP_TRAINING_PATTERN_SET,
			      DP_TRAINING_PATTERN_DISABLE);

	/* disable the training pattern on the source */
	if (ASIC_IS_DCE4(dp_info->rdev) || !dp_info->use_dpencoder)
		atombios_dig_encoder_setup(dp_info->encoder,
					   ATOM_ENCODER_CMD_DP_LINK_TRAINING_COMPLETE, 0);
	else
		radeon_dp_encoder_service(dp_info->rdev, ATOM_DP_ACTION_TRAINING_COMPLETE,
					  dp_info->dp_clock, dp_info->enc_id, 0);

	return 0;
}