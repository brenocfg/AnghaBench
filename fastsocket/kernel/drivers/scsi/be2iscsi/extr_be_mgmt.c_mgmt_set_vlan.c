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
typedef  int /*<<< orphan*/  uint16_t ;
struct beiscsi_hba {int dummy; } ;
struct be_mcc_wrb {int dummy; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_MBOX ; 
 int EBUSY ; 
 int /*<<< orphan*/  KERN_ERR ; 
 unsigned int be_cmd_set_vlan (struct beiscsi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*) ; 
 int beiscsi_mccq_compl (struct beiscsi_hba*,unsigned int,struct be_mcc_wrb**,int /*<<< orphan*/ *) ; 

int mgmt_set_vlan(struct beiscsi_hba *phba,
		   uint16_t vlan_tag)
{
	int rc;
	unsigned int tag;
	struct be_mcc_wrb *wrb = NULL;

	tag = be_cmd_set_vlan(phba, vlan_tag);
	if (!tag) {
		beiscsi_log(phba, KERN_ERR,
			    (BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX),
			    "BG_%d : VLAN Setting Failed\n");
		return -EBUSY;
	}

	rc = beiscsi_mccq_compl(phba, tag, &wrb, NULL);
	if (rc) {
		beiscsi_log(phba, KERN_ERR,
			    (BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX),
			    "BS_%d : VLAN MBX Cmd Failed\n");
		return rc;
	}
	return rc;
}