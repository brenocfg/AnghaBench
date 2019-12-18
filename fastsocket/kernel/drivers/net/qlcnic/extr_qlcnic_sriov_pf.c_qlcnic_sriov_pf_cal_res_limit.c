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
typedef  scalar_t__ u16 ;
struct qlcnic_vport {int /*<<< orphan*/  max_tx_bw; int /*<<< orphan*/  min_tx_bw; } ;
struct qlcnic_resources {int num_tx_queues; int num_rx_mcast_mac_filters; int num_tx_mac_filters; int num_destip; int num_rx_status_rings; int num_rx_buf_rings; int num_rx_queues; int num_lro_flows_supported; int /*<<< orphan*/  max_remote_ipv6_addrs; int /*<<< orphan*/  max_local_ipv6_addrs; int /*<<< orphan*/  num_txvlan_keys; } ;
struct qlcnic_sriov {int num_vfs; TYPE_2__* vf_info; struct qlcnic_resources ff_max; } ;
struct qlcnic_info {int bit_offsets; int max_tx_ques; int max_rx_mcast_mac_filters; int max_rx_ucast_mac_filters; int max_tx_mac_filters; int max_rx_ip_addr; int max_rx_status_rings; int max_rx_buf_rings; int max_rx_ques; int max_rx_lro_flow; int /*<<< orphan*/  max_remote_ipv6_addrs; int /*<<< orphan*/  max_local_ipv6_addrs; int /*<<< orphan*/  max_tx_vlan_keys; int /*<<< orphan*/  max_tx_bw; int /*<<< orphan*/  min_tx_bw; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_4__ {struct qlcnic_vport* vp; } ;
struct TYPE_3__ {scalar_t__ pci_func; struct qlcnic_sriov* sriov; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  MAX_BW ; 
 int QLCNIC_SRIOV_VF_MAX_MAC ; 
 int qlcnic_sriov_func_to_index (struct qlcnic_adapter*,scalar_t__) ; 
 int qlcnic_sriov_pf_get_vport_handle (struct qlcnic_adapter*,scalar_t__) ; 
 int qlcnic_sriov_pf_set_vport_info (struct qlcnic_adapter*,struct qlcnic_info*,int) ; 

__attribute__((used)) static int qlcnic_sriov_pf_cal_res_limit(struct qlcnic_adapter *adapter,
					 struct qlcnic_info *info, u16 func)
{
	struct qlcnic_sriov *sriov = adapter->ahw->sriov;
	struct qlcnic_resources *res = &sriov->ff_max;
	u32 temp, num_vf_macs, num_vfs, max;
	int ret = -EIO, vpid, id;
	struct qlcnic_vport *vp;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter, func);
	if (vpid < 0)
		return -EINVAL;

	num_vfs = sriov->num_vfs;
	max = num_vfs + 1;
	info->bit_offsets = 0xffff;
	info->max_tx_ques = res->num_tx_queues / max;
	info->max_rx_mcast_mac_filters = res->num_rx_mcast_mac_filters;
	num_vf_macs = QLCNIC_SRIOV_VF_MAX_MAC;

	if (adapter->ahw->pci_func == func) {
		temp = res->num_rx_mcast_mac_filters - (num_vfs * num_vf_macs);
		info->max_rx_ucast_mac_filters = temp;
		temp = res->num_tx_mac_filters - (num_vfs * num_vf_macs);
		info->max_tx_mac_filters = temp;
		info->min_tx_bw = 0;
		info->max_tx_bw = MAX_BW;
	} else {
		id = qlcnic_sriov_func_to_index(adapter, func);
		if (id < 0)
			return id;
		vp = sriov->vf_info[id].vp;
		info->min_tx_bw = vp->min_tx_bw;
		info->max_tx_bw = vp->max_tx_bw;
		info->max_rx_ucast_mac_filters = num_vf_macs;
		info->max_tx_mac_filters = num_vf_macs;
	}

	info->max_rx_ip_addr = res->num_destip / max;
	info->max_rx_status_rings = res->num_rx_status_rings / max;
	info->max_rx_buf_rings = res->num_rx_buf_rings / max;
	info->max_rx_ques = res->num_rx_queues / max;
	info->max_rx_lro_flow = res->num_lro_flows_supported / max;
	info->max_tx_vlan_keys = res->num_txvlan_keys;
	info->max_local_ipv6_addrs = res->max_local_ipv6_addrs;
	info->max_remote_ipv6_addrs = res->max_remote_ipv6_addrs;

	ret = qlcnic_sriov_pf_set_vport_info(adapter, info, vpid);
	if (ret)
		return ret;

	return 0;
}