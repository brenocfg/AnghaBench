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
struct TYPE_4__ {int ios_per_ctrl; int cxns_per_ctrl; int asyncpdus_per_ctrl; int icds_per_ctrl; int eq_timer; int num_eq_entries; int num_cq_entries; int wrbs_per_cxn; int /*<<< orphan*/  defpdu_data_sz; int /*<<< orphan*/  defpdu_hdr_sz; int /*<<< orphan*/  num_sge_per_io; } ;
struct TYPE_3__ {int iscsi_icd_count; int iscsi_cid_count; } ;
struct beiscsi_hba {TYPE_2__ params; TYPE_1__ fw_config; } ;

/* Variables and functions */
 int BE2_CMDS_PER_CXN ; 
 int /*<<< orphan*/  BE2_DEFPDU_DATA_SZ ; 
 int /*<<< orphan*/  BE2_DEFPDU_HDR_SZ ; 
 int BE2_NOPOUT_REQ ; 
 int /*<<< orphan*/  BE2_SGE ; 
 int BE2_TMFS ; 
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void beiscsi_get_params(struct beiscsi_hba *phba)
{
	phba->params.ios_per_ctrl = (phba->fw_config.iscsi_icd_count
				    - (phba->fw_config.iscsi_cid_count
				    + BE2_TMFS
				    + BE2_NOPOUT_REQ));
	phba->params.cxns_per_ctrl = phba->fw_config.iscsi_cid_count;
	phba->params.asyncpdus_per_ctrl = phba->fw_config.iscsi_cid_count;
	phba->params.icds_per_ctrl = phba->fw_config.iscsi_icd_count;
	phba->params.num_sge_per_io = BE2_SGE;
	phba->params.defpdu_hdr_sz = BE2_DEFPDU_HDR_SZ;
	phba->params.defpdu_data_sz = BE2_DEFPDU_DATA_SZ;
	phba->params.eq_timer = 64;
	phba->params.num_eq_entries =
	    (((BE2_CMDS_PER_CXN * 2 + phba->fw_config.iscsi_cid_count * 2
				    + BE2_TMFS) / 512) + 1) * 512;
	phba->params.num_eq_entries = (phba->params.num_eq_entries < 1024)
				? 1024 : phba->params.num_eq_entries;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
		    "BM_%d : phba->params.num_eq_entries=%d\n",
		    phba->params.num_eq_entries);
	phba->params.num_cq_entries =
	    (((BE2_CMDS_PER_CXN * 2 +  phba->fw_config.iscsi_cid_count * 2
				    + BE2_TMFS) / 512) + 1) * 512;
	phba->params.wrbs_per_cxn = 256;
}