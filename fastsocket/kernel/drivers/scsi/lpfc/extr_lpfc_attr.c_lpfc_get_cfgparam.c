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
struct lpfc_hba {scalar_t__ sli_rev; long cfg_soft_wwnn; long cfg_soft_wwpn; int cfg_enable_dss; scalar_t__ cfg_poll; } ;

/* Variables and functions */
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  lpfc_ack0 ; 
 int /*<<< orphan*/  lpfc_ack0_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_aer_support ; 
 int /*<<< orphan*/  lpfc_aer_support_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cr_count ; 
 int /*<<< orphan*/  lpfc_cr_count_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cr_delay ; 
 int /*<<< orphan*/  lpfc_cr_delay_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_bg ; 
 int /*<<< orphan*/  lpfc_enable_bg_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_hba_heartbeat ; 
 int /*<<< orphan*/  lpfc_enable_hba_heartbeat_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_hba_reset ; 
 int /*<<< orphan*/  lpfc_enable_hba_reset_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_npiv ; 
 int /*<<< orphan*/  lpfc_enable_npiv_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_enable_rrq ; 
 int /*<<< orphan*/  lpfc_enable_rrq_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcf_failover_policy ; 
 int /*<<< orphan*/  lpfc_fcf_failover_policy_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcp2_no_tgt_reset ; 
 int /*<<< orphan*/  lpfc_fcp2_no_tgt_reset_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcp_cpu_map ; 
 int /*<<< orphan*/  lpfc_fcp_cpu_map_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcp_imax ; 
 int /*<<< orphan*/  lpfc_fcp_imax_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcp_io_channel ; 
 int /*<<< orphan*/  lpfc_fcp_io_channel_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fcp_io_sched ; 
 int /*<<< orphan*/  lpfc_fcp_io_sched_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_hba_log_verbose_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_hba_queue_depth ; 
 int /*<<< orphan*/  lpfc_hba_queue_depth_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_iocb_cnt ; 
 int /*<<< orphan*/  lpfc_iocb_cnt_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_link_speed ; 
 int /*<<< orphan*/  lpfc_link_speed_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_log_verbose ; 
 int /*<<< orphan*/  lpfc_multi_ring_rctl ; 
 int /*<<< orphan*/  lpfc_multi_ring_rctl_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_multi_ring_support ; 
 int /*<<< orphan*/  lpfc_multi_ring_support_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_multi_ring_type ; 
 int /*<<< orphan*/  lpfc_multi_ring_type_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_poll ; 
 int /*<<< orphan*/  lpfc_poll_tmo ; 
 int /*<<< orphan*/  lpfc_poll_tmo_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_prot_sg_seg_cnt ; 
 int /*<<< orphan*/  lpfc_prot_sg_seg_cnt_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_req_fw_upgrade ; 
 int /*<<< orphan*/  lpfc_request_firmware_upgrade_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sg_seg_cnt ; 
 int /*<<< orphan*/  lpfc_sg_seg_cnt_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sriov_nr_virtfn ; 
 int /*<<< orphan*/  lpfc_sriov_nr_virtfn_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_suppress_link_up ; 
 int /*<<< orphan*/  lpfc_suppress_link_up_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_task_mgmt_tmo ; 
 int /*<<< orphan*/  lpfc_task_mgmt_tmo_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_topology ; 
 int /*<<< orphan*/  lpfc_topology_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_use_msi ; 
 int /*<<< orphan*/  lpfc_use_msi_init (struct lpfc_hba*,int /*<<< orphan*/ ) ; 

void
lpfc_get_cfgparam(struct lpfc_hba *phba)
{
	lpfc_fcp_io_sched_init(phba, lpfc_fcp_io_sched);
	lpfc_fcp2_no_tgt_reset_init(phba, lpfc_fcp2_no_tgt_reset);
	lpfc_cr_delay_init(phba, lpfc_cr_delay);
	lpfc_cr_count_init(phba, lpfc_cr_count);
	lpfc_multi_ring_support_init(phba, lpfc_multi_ring_support);
	lpfc_multi_ring_rctl_init(phba, lpfc_multi_ring_rctl);
	lpfc_multi_ring_type_init(phba, lpfc_multi_ring_type);
	lpfc_ack0_init(phba, lpfc_ack0);
	lpfc_topology_init(phba, lpfc_topology);
	lpfc_link_speed_init(phba, lpfc_link_speed);
	lpfc_poll_tmo_init(phba, lpfc_poll_tmo);
	lpfc_task_mgmt_tmo_init(phba, lpfc_task_mgmt_tmo);
	lpfc_enable_npiv_init(phba, lpfc_enable_npiv);
	lpfc_fcf_failover_policy_init(phba, lpfc_fcf_failover_policy);
	lpfc_enable_rrq_init(phba, lpfc_enable_rrq);
	lpfc_use_msi_init(phba, lpfc_use_msi);
	lpfc_fcp_imax_init(phba, lpfc_fcp_imax);
	lpfc_fcp_cpu_map_init(phba, lpfc_fcp_cpu_map);
	lpfc_fcp_io_channel_init(phba, lpfc_fcp_io_channel);
	lpfc_enable_hba_reset_init(phba, lpfc_enable_hba_reset);
	lpfc_enable_hba_heartbeat_init(phba, lpfc_enable_hba_heartbeat);
	lpfc_enable_bg_init(phba, lpfc_enable_bg);
	if (phba->sli_rev == LPFC_SLI_REV4)
		phba->cfg_poll = 0;
	else
	phba->cfg_poll = lpfc_poll;
	phba->cfg_soft_wwnn = 0L;
	phba->cfg_soft_wwpn = 0L;
	lpfc_sg_seg_cnt_init(phba, lpfc_sg_seg_cnt);
	lpfc_prot_sg_seg_cnt_init(phba, lpfc_prot_sg_seg_cnt);
	lpfc_hba_queue_depth_init(phba, lpfc_hba_queue_depth);
	lpfc_hba_log_verbose_init(phba, lpfc_log_verbose);
	lpfc_aer_support_init(phba, lpfc_aer_support);
	lpfc_sriov_nr_virtfn_init(phba, lpfc_sriov_nr_virtfn);
	lpfc_request_firmware_upgrade_init(phba, lpfc_req_fw_upgrade);
	lpfc_suppress_link_up_init(phba, lpfc_suppress_link_up);
	lpfc_iocb_cnt_init(phba, lpfc_iocb_cnt);
	phba->cfg_enable_dss = 1;
	return;
}