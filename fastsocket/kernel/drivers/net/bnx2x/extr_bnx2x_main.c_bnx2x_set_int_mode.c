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
struct bnx2x {int num_queues; int num_cnic_queues; int num_ethernet_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*,...) ; 
#define  BNX2X_INT_MODE_INTX 130 
#define  BNX2X_INT_MODE_MSI 129 
#define  BNX2X_INT_MODE_MSIX 128 
 int EINVAL ; 
 scalar_t__ IS_VF (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_enable_msi (struct bnx2x*) ; 
 int bnx2x_enable_msix (struct bnx2x*) ; 
 int int_mode ; 

int bnx2x_set_int_mode(struct bnx2x *bp)
{
	int rc = 0;

	if (IS_VF(bp) && int_mode != BNX2X_INT_MODE_MSIX)
		return -EINVAL;

	switch (int_mode) {
	case BNX2X_INT_MODE_MSIX:
		/* attempt to enable msix */
		rc = bnx2x_enable_msix(bp);

		/* msix attained */
		if (!rc)
			return 0;

		/* vfs use only msix */
		if (rc && IS_VF(bp))
			return rc;

		/* failed to enable multiple MSI-X */
		BNX2X_DEV_INFO("Failed to enable multiple MSI-X (%d), set number of queues to %d\n",
			       bp->num_queues,
			       1 + bp->num_cnic_queues);

		/* falling through... */
	case BNX2X_INT_MODE_MSI:
		bnx2x_enable_msi(bp);

		/* falling through... */
	case BNX2X_INT_MODE_INTX:
		bp->num_ethernet_queues = 1;
		bp->num_queues = bp->num_ethernet_queues + bp->num_cnic_queues;
		BNX2X_DEV_INFO("set number of queues to 1\n");
		break;
	default:
		BNX2X_DEV_INFO("unknown value in int_mode module parameter\n");
		return -EINVAL;
	}
	return 0;
}