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
struct bnx2i_hba {int /*<<< orphan*/  cnic_dev_type; } ;
struct Scsi_Host {void* can_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2I_NX2_DEV_5708 ; 
 int /*<<< orphan*/  BNX2I_NX2_DEV_5709 ; 
 int /*<<< orphan*/  BNX2I_NX2_DEV_57710 ; 
 void* ISCSI_MAX_CMDS_PER_HBA_5708 ; 
 void* ISCSI_MAX_CMDS_PER_HBA_5709 ; 
 void* ISCSI_MAX_CMDS_PER_HBA_57710 ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2i_setup_host_queue_size(struct bnx2i_hba *hba,
					struct Scsi_Host *shost)
{
	if (test_bit(BNX2I_NX2_DEV_5708, &hba->cnic_dev_type))
		shost->can_queue = ISCSI_MAX_CMDS_PER_HBA_5708;
	else if (test_bit(BNX2I_NX2_DEV_5709, &hba->cnic_dev_type))
		shost->can_queue = ISCSI_MAX_CMDS_PER_HBA_5709;
	else if (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type))
		shost->can_queue = ISCSI_MAX_CMDS_PER_HBA_57710;
	else
		shost->can_queue = ISCSI_MAX_CMDS_PER_HBA_5708;
}