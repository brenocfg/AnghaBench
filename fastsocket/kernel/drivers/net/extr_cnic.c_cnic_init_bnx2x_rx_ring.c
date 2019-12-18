#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_12__ {int /*<<< orphan*/ * index_values; } ;
struct host_sp_status_block {TYPE_6__ sp_sb; } ;
struct eth_rx_cqe_next_page {void* addr_lo; void* addr_hi; } ;
struct eth_rx_bd {void* addr_lo; void* addr_hi; } ;
struct cnic_uio_dev {int l2_ring_map; int l2_buf_map; scalar_t__ l2_ring; } ;
struct cnic_local {int l2_single_buf_size; int l2_rx_ring_size; int /*<<< orphan*/ * rx_cons_ptr; int /*<<< orphan*/  rx_cons; int /*<<< orphan*/  pfid; TYPE_1__* ethdev; struct host_sp_status_block* bnx2x_def_status_blk; struct cnic_uio_dev* udev; } ;
struct cnic_dev {int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;
struct TYPE_10__ {void* lo; void* hi; } ;
struct TYPE_9__ {void* lo; void* hi; } ;
struct TYPE_11__ {int client_qzone_id; size_t rx_sb_index_number; int outer_vlan_removal_enable_flg; int silent_vlan_removal_flg; int silent_vlan_mask; scalar_t__ silent_vlan_value; void* max_bytes_on_bd; int /*<<< orphan*/  cache_line_alignment_log_size; int /*<<< orphan*/  status_block_id; TYPE_4__ cqe_page_base; TYPE_3__ bd_page_base; } ;
struct TYPE_8__ {int client_id; int activate_flg; int sp_client_id; int /*<<< orphan*/  func_id; void* mtu; } ;
struct client_init_ramrod_data {TYPE_5__ rx; TYPE_2__ general; } ;
struct bnx2x {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_7__ {int iscsi_l2_client_id; } ;

/* Variables and functions */
 int BNX2X_CL_QZONE_ID (struct bnx2x*,int) ; 
 int /*<<< orphan*/  BNX2X_DEF_SB_ID ; 
 int /*<<< orphan*/  BNX2X_MAX_RCQ_DESC_CNT ; 
 int BNX2X_MAX_RX_DESC_CNT ; 
 int BNX2_PAGE_SIZE ; 
 size_t HC_SP_INDEX_ETH_ISCSI_RX_CQ_CONS ; 
 int /*<<< orphan*/  L1_CACHE_SHIFT ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 struct bnx2x* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnic_init_bnx2x_rx_ring(struct cnic_dev *dev,
				    struct client_init_ramrod_data *data)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct bnx2x *bp = netdev_priv(dev->netdev);
	struct cnic_uio_dev *udev = cp->udev;
	struct eth_rx_bd *rxbd = (struct eth_rx_bd *) (udev->l2_ring +
				BNX2_PAGE_SIZE);
	struct eth_rx_cqe_next_page *rxcqe = (struct eth_rx_cqe_next_page *)
				(udev->l2_ring + (2 * BNX2_PAGE_SIZE));
	struct host_sp_status_block *sb = cp->bnx2x_def_status_blk;
	int i;
	u32 cli = cp->ethdev->iscsi_l2_client_id;
	int cl_qzone_id = BNX2X_CL_QZONE_ID(bp, cli);
	u32 val;
	dma_addr_t ring_map = udev->l2_ring_map;

	/* General data */
	data->general.client_id = cli;
	data->general.activate_flg = 1;
	data->general.sp_client_id = cli;
	data->general.mtu = cpu_to_le16(cp->l2_single_buf_size - 14);
	data->general.func_id = cp->pfid;

	for (i = 0; i < BNX2X_MAX_RX_DESC_CNT; i++, rxbd++) {
		dma_addr_t buf_map;
		int n = (i % cp->l2_rx_ring_size) + 1;

		buf_map = udev->l2_buf_map + (n * cp->l2_single_buf_size);
		rxbd->addr_hi = cpu_to_le32((u64) buf_map >> 32);
		rxbd->addr_lo = cpu_to_le32(buf_map & 0xffffffff);
	}

	val = (u64) (ring_map + BNX2_PAGE_SIZE) >> 32;
	rxbd->addr_hi = cpu_to_le32(val);
	data->rx.bd_page_base.hi = cpu_to_le32(val);

	val = (u64) (ring_map + BNX2_PAGE_SIZE) & 0xffffffff;
	rxbd->addr_lo = cpu_to_le32(val);
	data->rx.bd_page_base.lo = cpu_to_le32(val);

	rxcqe += BNX2X_MAX_RCQ_DESC_CNT;
	val = (u64) (ring_map + (2 * BNX2_PAGE_SIZE)) >> 32;
	rxcqe->addr_hi = cpu_to_le32(val);
	data->rx.cqe_page_base.hi = cpu_to_le32(val);

	val = (u64) (ring_map + (2 * BNX2_PAGE_SIZE)) & 0xffffffff;
	rxcqe->addr_lo = cpu_to_le32(val);
	data->rx.cqe_page_base.lo = cpu_to_le32(val);

	/* Other ramrod params */
	data->rx.client_qzone_id = cl_qzone_id;
	data->rx.rx_sb_index_number = HC_SP_INDEX_ETH_ISCSI_RX_CQ_CONS;
	data->rx.status_block_id = BNX2X_DEF_SB_ID;

	data->rx.cache_line_alignment_log_size = L1_CACHE_SHIFT;

	data->rx.max_bytes_on_bd = cpu_to_le16(cp->l2_single_buf_size);
	data->rx.outer_vlan_removal_enable_flg = 1;
	data->rx.silent_vlan_removal_flg = 1;
	data->rx.silent_vlan_value = 0;
	data->rx.silent_vlan_mask = 0xffff;

	cp->rx_cons_ptr =
		&sb->sp_sb.index_values[HC_SP_INDEX_ETH_ISCSI_RX_CQ_CONS];
	cp->rx_cons = *cp->rx_cons_ptr;
}