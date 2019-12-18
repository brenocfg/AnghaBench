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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pmf; } ;
struct bnx2x {int flags; scalar_t__ dcbx_enabled; scalar_t__ dcb_state; TYPE_1__ port; } ;

/* Variables and functions */
 int BC_SUPPORTS_DCBX_MSG_NON_PMF ; 
 scalar_t__ BNX2X_DCB_STATE_ON ; 
 int /*<<< orphan*/  BNX2X_MSG_DCB ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int DRV_FLAGS_DCB_CONFIGURED ; 
 int /*<<< orphan*/  DRV_MSG_CODE_DCBX_ADMIN_PMF_MSG ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_DCBX_ADMIN_MIB ; 
 scalar_t__ SHMEM2_HAS (struct bnx2x*,scalar_t__) ; 
 scalar_t__ SHMEM2_RD (struct bnx2x*,scalar_t__) ; 
 scalar_t__ SHMEM_LLDP_DCBX_PARAMS_NONE ; 
 int /*<<< orphan*/  bnx2x_acquire_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_dcbx_admin_mib_updated_params (struct bnx2x*,scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_fw_command (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_release_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_update_drv_flags (struct bnx2x*,int,int /*<<< orphan*/ ) ; 

void bnx2x_dcbx_init(struct bnx2x *bp, bool update_shmem)
{
	u32 dcbx_lldp_params_offset = SHMEM_LLDP_DCBX_PARAMS_NONE;

	/* only PMF can send ADMIN msg to MFW in old MFW versions */
	if ((!bp->port.pmf) && (!(bp->flags & BC_SUPPORTS_DCBX_MSG_NON_PMF)))
		return;

	if (bp->dcbx_enabled <= 0)
		return;

	/* validate:
	 * chip of good for dcbx version,
	 * dcb is wanted
	 * shmem2 contains DCBX support fields
	 */
	DP(BNX2X_MSG_DCB, "dcb_state %d bp->port.pmf %d\n",
	   bp->dcb_state, bp->port.pmf);

	if (bp->dcb_state == BNX2X_DCB_STATE_ON &&
	    SHMEM2_HAS(bp, dcbx_lldp_params_offset)) {
		dcbx_lldp_params_offset =
			SHMEM2_RD(bp, dcbx_lldp_params_offset);

		DP(BNX2X_MSG_DCB, "dcbx_lldp_params_offset 0x%x\n",
		   dcbx_lldp_params_offset);

		bnx2x_update_drv_flags(bp, 1 << DRV_FLAGS_DCB_CONFIGURED, 0);

		if (SHMEM_LLDP_DCBX_PARAMS_NONE != dcbx_lldp_params_offset) {
			/* need HW lock to avoid scenario of two drivers
			 * writing in parallel to shmem
			 */
			bnx2x_acquire_hw_lock(bp,
					      HW_LOCK_RESOURCE_DCBX_ADMIN_MIB);
			if (update_shmem)
				bnx2x_dcbx_admin_mib_updated_params(bp,
					dcbx_lldp_params_offset);

			/* Let HW start negotiation */
			bnx2x_fw_command(bp,
					 DRV_MSG_CODE_DCBX_ADMIN_PMF_MSG, 0);
			/* release HW lock only after MFW acks that it finished
			 * reading values from shmem
			 */
			bnx2x_release_hw_lock(bp,
					      HW_LOCK_RESOURCE_DCBX_ADMIN_MIB);
		}
	}
}