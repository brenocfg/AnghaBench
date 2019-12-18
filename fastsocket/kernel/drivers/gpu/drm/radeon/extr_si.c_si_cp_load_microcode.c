#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {TYPE_3__* me_fw; TYPE_2__* ce_fw; TYPE_1__* pfp_fw; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_CE_UCODE_ADDR ; 
 int /*<<< orphan*/  CP_CE_UCODE_DATA ; 
 int /*<<< orphan*/  CP_ME_RAM_DATA ; 
 int /*<<< orphan*/  CP_ME_RAM_RADDR ; 
 int /*<<< orphan*/  CP_ME_RAM_WADDR ; 
 int /*<<< orphan*/  CP_PFP_UCODE_ADDR ; 
 int /*<<< orphan*/  CP_PFP_UCODE_DATA ; 
 int EINVAL ; 
 int SI_CE_UCODE_SIZE ; 
 int SI_PFP_UCODE_SIZE ; 
 int SI_PM4_UCODE_SIZE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_cp_enable (struct radeon_device*,int) ; 

__attribute__((used)) static int si_cp_load_microcode(struct radeon_device *rdev)
{
	const __be32 *fw_data;
	int i;

	if (!rdev->me_fw || !rdev->pfp_fw)
		return -EINVAL;

	si_cp_enable(rdev, false);

	/* PFP */
	fw_data = (const __be32 *)rdev->pfp_fw->data;
	WREG32(CP_PFP_UCODE_ADDR, 0);
	for (i = 0; i < SI_PFP_UCODE_SIZE; i++)
		WREG32(CP_PFP_UCODE_DATA, be32_to_cpup(fw_data++));
	WREG32(CP_PFP_UCODE_ADDR, 0);

	/* CE */
	fw_data = (const __be32 *)rdev->ce_fw->data;
	WREG32(CP_CE_UCODE_ADDR, 0);
	for (i = 0; i < SI_CE_UCODE_SIZE; i++)
		WREG32(CP_CE_UCODE_DATA, be32_to_cpup(fw_data++));
	WREG32(CP_CE_UCODE_ADDR, 0);

	/* ME */
	fw_data = (const __be32 *)rdev->me_fw->data;
	WREG32(CP_ME_RAM_WADDR, 0);
	for (i = 0; i < SI_PM4_UCODE_SIZE; i++)
		WREG32(CP_ME_RAM_DATA, be32_to_cpup(fw_data++));
	WREG32(CP_ME_RAM_WADDR, 0);

	WREG32(CP_PFP_UCODE_ADDR, 0);
	WREG32(CP_CE_UCODE_ADDR, 0);
	WREG32(CP_ME_RAM_WADDR, 0);
	WREG32(CP_ME_RAM_RADDR, 0);
	return 0;
}