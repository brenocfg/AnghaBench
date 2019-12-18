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
struct TYPE_2__ {scalar_t__ shmem2_base; } ;
struct bnx2x {int afex_def_vlan_tag; TYPE_1__ common; } ;

/* Variables and functions */
 int FW_MSG_CODE_DRV_LOAD_COMMON ; 
 int FW_MSG_CODE_DRV_LOAD_COMMON_CHIP ; 
 scalar_t__ SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM2_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int SHMEM_AFEX_SUPPORTED_VERSION_ONE ; 
 int SHMEM_DCC_SUPPORT_BANDWIDTH_ALLOCATION_TLV ; 
 int SHMEM_DCC_SUPPORT_DISABLE_ENABLE_PF_TLV ; 
 int /*<<< orphan*/  afex_driver_support ; 
 int /*<<< orphan*/  dcc_support ; 

__attribute__((used)) static void bnx2x_nic_load_afex_dcc(struct bnx2x *bp, int load_code)
{
	if (((load_code == FW_MSG_CODE_DRV_LOAD_COMMON) ||
	     (load_code == FW_MSG_CODE_DRV_LOAD_COMMON_CHIP)) &&
	    (bp->common.shmem2_base)) {
		if (SHMEM2_HAS(bp, dcc_support))
			SHMEM2_WR(bp, dcc_support,
				  (SHMEM_DCC_SUPPORT_DISABLE_ENABLE_PF_TLV |
				   SHMEM_DCC_SUPPORT_BANDWIDTH_ALLOCATION_TLV));
		if (SHMEM2_HAS(bp, afex_driver_support))
			SHMEM2_WR(bp, afex_driver_support,
				  SHMEM_AFEX_SUPPORTED_VERSION_ONE);
	}

	/* Set AFEX default VLAN tag to an invalid value */
	bp->afex_def_vlan_tag = -1;
}