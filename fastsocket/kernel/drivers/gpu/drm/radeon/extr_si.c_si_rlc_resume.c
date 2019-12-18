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
typedef  int u32 ;
struct TYPE_3__ {int save_restore_gpu_addr; int clear_state_gpu_addr; } ;
struct radeon_device {TYPE_2__* rlc_fw; TYPE_1__ rlc; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RLC_CLEAR_STATE_RESTORE_BASE ; 
 int /*<<< orphan*/  RLC_LB_CNTL ; 
 int /*<<< orphan*/  RLC_LB_CNTR_INIT ; 
 int /*<<< orphan*/  RLC_LB_CNTR_MAX ; 
 int /*<<< orphan*/  RLC_MC_CNTL ; 
 int /*<<< orphan*/  RLC_RL_BASE ; 
 int /*<<< orphan*/  RLC_RL_SIZE ; 
 int /*<<< orphan*/  RLC_SAVE_AND_RESTORE_BASE ; 
 int /*<<< orphan*/  RLC_UCODE_ADDR ; 
 int /*<<< orphan*/  RLC_UCODE_CNTL ; 
 int /*<<< orphan*/  RLC_UCODE_DATA ; 
 int SI_RLC_UCODE_SIZE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_rlc_start (struct radeon_device*) ; 
 int /*<<< orphan*/  si_rlc_stop (struct radeon_device*) ; 

__attribute__((used)) static int si_rlc_resume(struct radeon_device *rdev)
{
	u32 i;
	const __be32 *fw_data;

	if (!rdev->rlc_fw)
		return -EINVAL;

	si_rlc_stop(rdev);

	WREG32(RLC_RL_BASE, 0);
	WREG32(RLC_RL_SIZE, 0);
	WREG32(RLC_LB_CNTL, 0);
	WREG32(RLC_LB_CNTR_MAX, 0xffffffff);
	WREG32(RLC_LB_CNTR_INIT, 0);

	WREG32(RLC_SAVE_AND_RESTORE_BASE, rdev->rlc.save_restore_gpu_addr >> 8);
	WREG32(RLC_CLEAR_STATE_RESTORE_BASE, rdev->rlc.clear_state_gpu_addr >> 8);

	WREG32(RLC_MC_CNTL, 0);
	WREG32(RLC_UCODE_CNTL, 0);

	fw_data = (const __be32 *)rdev->rlc_fw->data;
	for (i = 0; i < SI_RLC_UCODE_SIZE; i++) {
		WREG32(RLC_UCODE_ADDR, i);
		WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
	}
	WREG32(RLC_UCODE_ADDR, 0);

	si_rlc_start(rdev);

	return 0;
}