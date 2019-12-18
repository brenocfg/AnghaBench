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
struct radeon_device {scalar_t__ family; TYPE_2__* rlc_fw; TYPE_1__ rlc; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARUBA_RLC_UCODE_SIZE ; 
 int CAYMAN_RLC_UCODE_SIZE ; 
 scalar_t__ CHIP_ARUBA ; 
 scalar_t__ CHIP_CAICOS ; 
 scalar_t__ CHIP_CAYMAN ; 
 scalar_t__ CHIP_CEDAR ; 
 scalar_t__ CHIP_RV770 ; 
 int EINVAL ; 
 int EVERGREEN_RLC_UCODE_SIZE ; 
 int R700_RLC_UCODE_SIZE ; 
 int /*<<< orphan*/  RLC_HB_BASE ; 
 int /*<<< orphan*/  RLC_HB_CNTL ; 
 int /*<<< orphan*/  RLC_HB_RPTR ; 
 int /*<<< orphan*/  RLC_HB_WPTR ; 
 int /*<<< orphan*/  RLC_HB_WPTR_LSB_ADDR ; 
 int /*<<< orphan*/  RLC_HB_WPTR_MSB_ADDR ; 
 int /*<<< orphan*/  RLC_MC_CNTL ; 
 int /*<<< orphan*/  RLC_UCODE_ADDR ; 
 int /*<<< orphan*/  RLC_UCODE_CNTL ; 
 int /*<<< orphan*/  RLC_UCODE_DATA ; 
 int RLC_UCODE_SIZE ; 
 int /*<<< orphan*/  TN_RLC_CLEAR_STATE_RESTORE_BASE ; 
 int /*<<< orphan*/  TN_RLC_SAVE_AND_RESTORE_BASE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_rlc_start (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_rlc_stop (struct radeon_device*) ; 

__attribute__((used)) static int r600_rlc_init(struct radeon_device *rdev)
{
	u32 i;
	const __be32 *fw_data;

	if (!rdev->rlc_fw)
		return -EINVAL;

	r600_rlc_stop(rdev);

	WREG32(RLC_HB_CNTL, 0);

	if (rdev->family == CHIP_ARUBA) {
		WREG32(TN_RLC_SAVE_AND_RESTORE_BASE, rdev->rlc.save_restore_gpu_addr >> 8);
		WREG32(TN_RLC_CLEAR_STATE_RESTORE_BASE, rdev->rlc.clear_state_gpu_addr >> 8);
	}
	if (rdev->family <= CHIP_CAYMAN) {
		WREG32(RLC_HB_BASE, 0);
		WREG32(RLC_HB_RPTR, 0);
		WREG32(RLC_HB_WPTR, 0);
	}
	if (rdev->family <= CHIP_CAICOS) {
		WREG32(RLC_HB_WPTR_LSB_ADDR, 0);
		WREG32(RLC_HB_WPTR_MSB_ADDR, 0);
	}
	WREG32(RLC_MC_CNTL, 0);
	WREG32(RLC_UCODE_CNTL, 0);

	fw_data = (const __be32 *)rdev->rlc_fw->data;
	if (rdev->family >= CHIP_ARUBA) {
		for (i = 0; i < ARUBA_RLC_UCODE_SIZE; i++) {
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		}
	} else if (rdev->family >= CHIP_CAYMAN) {
		for (i = 0; i < CAYMAN_RLC_UCODE_SIZE; i++) {
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		}
	} else if (rdev->family >= CHIP_CEDAR) {
		for (i = 0; i < EVERGREEN_RLC_UCODE_SIZE; i++) {
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		}
	} else if (rdev->family >= CHIP_RV770) {
		for (i = 0; i < R700_RLC_UCODE_SIZE; i++) {
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		}
	} else {
		for (i = 0; i < RLC_UCODE_SIZE; i++) {
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		}
	}
	WREG32(RLC_UCODE_ADDR, 0);

	r600_rlc_start(rdev);

	return 0;
}