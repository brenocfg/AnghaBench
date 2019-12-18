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
struct qlcnic_info {int total_pf; int total_rss_engines; void* max_remote_ipv6_addrs; void* max_local_ipv6_addrs; void* max_tx_vlan_keys; void* max_rx_ques; void* max_rx_buf_rings; void* max_rx_status_rings; void* max_rx_lro_flow; void* max_rx_ip_addr; void* max_rx_ucast_mac_filters; void* max_rx_mcast_mac_filters; void* max_tx_mac_filters; void* max_tx_ques; void* max_vports; } ;
struct TYPE_5__ {int* arg; } ;
struct TYPE_4__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ rsp; TYPE_1__ req; } ;
struct qlcnic_adapter {TYPE_3__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* LSW (int) ; 
 void* MSW (int) ; 
 int /*<<< orphan*/  QLCNIC_CMD_GET_NIC_INFO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*) ; 
 scalar_t__ qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_set_ff_max_res (struct qlcnic_adapter*,struct qlcnic_info*) ; 

__attribute__((used)) static int qlcnic_sriov_get_pf_info(struct qlcnic_adapter *adapter,
				    struct qlcnic_info *npar_info)
{
	int err;
	struct qlcnic_cmd_args cmd;

	if (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_NIC_INFO))
		return -ENOMEM;

	cmd.req.arg[1] = 0x2;
	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err) {
		dev_err(&adapter->pdev->dev,
			"Failed to get PF info, err=%d\n", err);
		goto out;
	}

	npar_info->total_pf = cmd.rsp.arg[2] & 0xff;
	npar_info->total_rss_engines = (cmd.rsp.arg[2] >> 8) & 0xff;
	npar_info->max_vports = MSW(cmd.rsp.arg[2]);
	npar_info->max_tx_ques =  LSW(cmd.rsp.arg[3]);
	npar_info->max_tx_mac_filters = MSW(cmd.rsp.arg[3]);
	npar_info->max_rx_mcast_mac_filters = LSW(cmd.rsp.arg[4]);
	npar_info->max_rx_ucast_mac_filters = MSW(cmd.rsp.arg[4]);
	npar_info->max_rx_ip_addr = LSW(cmd.rsp.arg[5]);
	npar_info->max_rx_lro_flow = MSW(cmd.rsp.arg[5]);
	npar_info->max_rx_status_rings = LSW(cmd.rsp.arg[6]);
	npar_info->max_rx_buf_rings = MSW(cmd.rsp.arg[6]);
	npar_info->max_rx_ques = LSW(cmd.rsp.arg[7]);
	npar_info->max_tx_vlan_keys = MSW(cmd.rsp.arg[7]);
	npar_info->max_local_ipv6_addrs = LSW(cmd.rsp.arg[8]);
	npar_info->max_remote_ipv6_addrs = MSW(cmd.rsp.arg[8]);

	qlcnic_sriov_pf_set_ff_max_res(adapter, npar_info);
	dev_info(&adapter->pdev->dev,
		 "\n\ttotal_pf: %d,\n"
		 "\n\ttotal_rss_engines: %d max_vports: %d max_tx_ques %d,\n"
		 "\tmax_tx_mac_filters: %d max_rx_mcast_mac_filters: %d,\n"
		 "\tmax_rx_ucast_mac_filters: 0x%x, max_rx_ip_addr: %d,\n"
		 "\tmax_rx_lro_flow: %d max_rx_status_rings: %d,\n"
		 "\tmax_rx_buf_rings: %d, max_rx_ques: %d, max_tx_vlan_keys %d\n"
		 "\tmax_local_ipv6_addrs: %d, max_remote_ipv6_addrs: %d\n",
		 npar_info->total_pf, npar_info->total_rss_engines,
		 npar_info->max_vports, npar_info->max_tx_ques,
		 npar_info->max_tx_mac_filters,
		 npar_info->max_rx_mcast_mac_filters,
		 npar_info->max_rx_ucast_mac_filters, npar_info->max_rx_ip_addr,
		 npar_info->max_rx_lro_flow, npar_info->max_rx_status_rings,
		 npar_info->max_rx_buf_rings, npar_info->max_rx_ques,
		 npar_info->max_tx_vlan_keys, npar_info->max_local_ipv6_addrs,
		 npar_info->max_remote_ipv6_addrs);

out:
	qlcnic_free_mbx_args(&cmd);
	return err;
}