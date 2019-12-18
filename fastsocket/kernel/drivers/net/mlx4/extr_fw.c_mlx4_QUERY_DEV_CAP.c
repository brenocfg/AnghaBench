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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct mlx4_dev_cap {int reserved_qps; int max_qps; int reserved_srqs; int max_srqs; int max_cq_sz; int reserved_cqs; int max_cqs; int max_mpts; int reserved_eqs; int max_eqs; int reserved_mtts; int max_mrw_sz; int reserved_mrws; int max_mtt_seg; int max_requester_per_qp; int max_responder_per_qp; int max_gso_sz; int max_rss_tbl_sz; int max_rdma_global; int local_ca_ack_delay; int num_ports; int max_msg_sz; int fs_log_max_ucast_qp_range_size; int fs_max_num_qp_per_entry; int stat_rate_support; int flags; int reserved_uars; int uar_size; int min_page_sz; int bf_reg_size; int bf_regs_per_page; int max_sq_sg; int max_sq_desc_sz; int max_qp_per_mcg; int reserved_mgms; int max_mcgs; int reserved_pds; int max_pds; int reserved_xrcds; int max_xrcds; int rdmarc_entry_sz; int qpc_entry_sz; int aux_entry_sz; int altc_entry_sz; int eqc_entry_sz; int cqc_entry_sz; int srq_entry_sz; int cmpt_entry_sz; int mtt_entry_sz; int dmpt_entry_sz; int max_srq_sz; int max_qp_sz; int resize_srq; int max_rq_sg; int max_rq_desc_sz; int bmme_flags; int reserved_lkey; int max_icm_sz; int max_counters; int* max_vl; int* ib_mtu; int* max_port_width; int* max_gids; int* max_pkeys; int* supported_port_types; int* suggested_type; int* default_sense; int* log_max_macs; int* log_max_vlans; int* eth_mtu; int* def_mac; int /*<<< orphan*/  flags2; } ;
struct mlx4_dev {int flags; } ;
struct mlx4_cmd_mailbox {int* buf; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_QUERY_DEV_CAP ; 
 int /*<<< orphan*/  MLX4_CMD_QUERY_PORT ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_B ; 
 int /*<<< orphan*/  MLX4_DEV_CAP_FLAG2_FS_EN ; 
 int /*<<< orphan*/  MLX4_DEV_CAP_FLAG2_RSS ; 
 int /*<<< orphan*/  MLX4_DEV_CAP_FLAG2_RSS_TOP ; 
 int /*<<< orphan*/  MLX4_DEV_CAP_FLAG2_RSS_XOR ; 
 int /*<<< orphan*/  MLX4_DEV_CAP_FLAG2_TS ; 
 int /*<<< orphan*/  MLX4_DEV_CAP_FLAG2_UPDATE_QP ; 
 int /*<<< orphan*/  MLX4_DEV_CAP_FLAG2_VLAN_CONTROL ; 
 int /*<<< orphan*/  MLX4_DEV_CAP_FLAGS2_REASSIGN_MAC_EN ; 
 int MLX4_DEV_CAP_FLAG_COUNTERS ; 
 int MLX4_FLAG_OLD_PORT_CMDS ; 
 int /*<<< orphan*/  MLX4_GET (int,int*,int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_ACK_DELAY_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_ALTC_ENTRY_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_AUX_ENTRY_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_BF_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_BMME_FLAGS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_CQC_ENTRY_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_C_MPT_ENTRY_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_D_MPT_ENTRY_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_EQC_ENTRY_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_EXT_FLAGS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_FLAGS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_FLOW_STEERING_MAX_QP_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_FW_REASSIGN_MAC ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_LOG_BF_REG_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_LOG_MAX_BF_REGS_PER_PAGE_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_COUNTERS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_CQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_CQ_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_DESC_SZ_RQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_DESC_SZ_SQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_EQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_GID_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_GSO_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_ICM_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_MCG_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_MPT_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_MRW_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_MSG_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_MTT_SEG_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_PD_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_PKEY_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_QP_MCG_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_QP_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_QP_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_RDMA_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_REQ_QP_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_RES_QP_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_SG_RQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_SG_SQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_SRQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_SRQ_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MAX_XRC_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MTT_ENTRY_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_MTU_WIDTH_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_PAGE_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_QPC_ENTRY_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RATE_SUPPORT_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RDMARC_ENTRY_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSVD_CQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSVD_EQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSVD_LKEY_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSVD_MCG_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSVD_MRW_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSVD_MTT_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSVD_PD_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSVD_QP_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSVD_SRQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSVD_UAR_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSVD_XRC_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_RSZ_SRQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_SRQ_ENTRY_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_UAR_SZ_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_VL_PORT_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_ETH_MTU_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_MAC_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_MAX_GID_PKEY_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_MAX_MACVLAN_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_MAX_VL_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_MTU_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_SUPPORTED_TYPE_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_WIDTH_OFFSET ; 
 int /*<<< orphan*/  dump_dev_cap_flags (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  dump_dev_cap_flags2 (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_QUERY_DEV_CAP(struct mlx4_dev *dev, struct mlx4_dev_cap *dev_cap)
{
	struct mlx4_cmd_mailbox *mailbox;
	u32 *outbox;
	u8 field;
	u32 field32, flags, ext_flags;
	u16 size;
	u16 stat_rate;
	int err;
	int i;

#define QUERY_DEV_CAP_OUT_SIZE		       0x100
#define QUERY_DEV_CAP_MAX_SRQ_SZ_OFFSET		0x10
#define QUERY_DEV_CAP_MAX_QP_SZ_OFFSET		0x11
#define QUERY_DEV_CAP_RSVD_QP_OFFSET		0x12
#define QUERY_DEV_CAP_MAX_QP_OFFSET		0x13
#define QUERY_DEV_CAP_RSVD_SRQ_OFFSET		0x14
#define QUERY_DEV_CAP_MAX_SRQ_OFFSET		0x15
#define QUERY_DEV_CAP_RSVD_EEC_OFFSET		0x16
#define QUERY_DEV_CAP_MAX_EEC_OFFSET		0x17
#define QUERY_DEV_CAP_MAX_CQ_SZ_OFFSET		0x19
#define QUERY_DEV_CAP_RSVD_CQ_OFFSET		0x1a
#define QUERY_DEV_CAP_MAX_CQ_OFFSET		0x1b
#define QUERY_DEV_CAP_MAX_MPT_OFFSET		0x1d
#define QUERY_DEV_CAP_RSVD_EQ_OFFSET		0x1e
#define QUERY_DEV_CAP_MAX_EQ_OFFSET		0x1f
#define QUERY_DEV_CAP_RSVD_MTT_OFFSET		0x20
#define QUERY_DEV_CAP_MAX_MRW_SZ_OFFSET		0x21
#define QUERY_DEV_CAP_RSVD_MRW_OFFSET		0x22
#define QUERY_DEV_CAP_MAX_MTT_SEG_OFFSET	0x23
#define QUERY_DEV_CAP_MAX_AV_OFFSET		0x27
#define QUERY_DEV_CAP_MAX_REQ_QP_OFFSET		0x29
#define QUERY_DEV_CAP_MAX_RES_QP_OFFSET		0x2b
#define QUERY_DEV_CAP_MAX_GSO_OFFSET		0x2d
#define QUERY_DEV_CAP_RSS_OFFSET		0x2e
#define QUERY_DEV_CAP_MAX_RDMA_OFFSET		0x2f
#define QUERY_DEV_CAP_RSZ_SRQ_OFFSET		0x33
#define QUERY_DEV_CAP_ACK_DELAY_OFFSET		0x35
#define QUERY_DEV_CAP_MTU_WIDTH_OFFSET		0x36
#define QUERY_DEV_CAP_VL_PORT_OFFSET		0x37
#define QUERY_DEV_CAP_MAX_MSG_SZ_OFFSET		0x38
#define QUERY_DEV_CAP_MAX_GID_OFFSET		0x3b
#define QUERY_DEV_CAP_RATE_SUPPORT_OFFSET	0x3c
#define QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET	0x3e
#define QUERY_DEV_CAP_MAX_PKEY_OFFSET		0x3f
#define QUERY_DEV_CAP_EXT_FLAGS_OFFSET		0x40
#define QUERY_DEV_CAP_FLAGS_OFFSET		0x44
#define QUERY_DEV_CAP_RSVD_UAR_OFFSET		0x48
#define QUERY_DEV_CAP_UAR_SZ_OFFSET		0x49
#define QUERY_DEV_CAP_PAGE_SZ_OFFSET		0x4b
#define QUERY_DEV_CAP_BF_OFFSET			0x4c
#define QUERY_DEV_CAP_LOG_BF_REG_SZ_OFFSET	0x4d
#define QUERY_DEV_CAP_LOG_MAX_BF_REGS_PER_PAGE_OFFSET	0x4e
#define QUERY_DEV_CAP_LOG_MAX_BF_PAGES_OFFSET	0x4f
#define QUERY_DEV_CAP_MAX_SG_SQ_OFFSET		0x51
#define QUERY_DEV_CAP_MAX_DESC_SZ_SQ_OFFSET	0x52
#define QUERY_DEV_CAP_MAX_SG_RQ_OFFSET		0x55
#define QUERY_DEV_CAP_MAX_DESC_SZ_RQ_OFFSET	0x56
#define QUERY_DEV_CAP_MAX_QP_MCG_OFFSET		0x61
#define QUERY_DEV_CAP_RSVD_MCG_OFFSET		0x62
#define QUERY_DEV_CAP_MAX_MCG_OFFSET		0x63
#define QUERY_DEV_CAP_RSVD_PD_OFFSET		0x64
#define QUERY_DEV_CAP_MAX_PD_OFFSET		0x65
#define QUERY_DEV_CAP_RSVD_XRC_OFFSET		0x66
#define QUERY_DEV_CAP_MAX_XRC_OFFSET		0x67
#define QUERY_DEV_CAP_MAX_COUNTERS_OFFSET	0x68
#define QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET	0x70
#define QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET	0x76
#define QUERY_DEV_CAP_FLOW_STEERING_MAX_QP_OFFSET	0x77
#define QUERY_DEV_CAP_RDMARC_ENTRY_SZ_OFFSET	0x80
#define QUERY_DEV_CAP_QPC_ENTRY_SZ_OFFSET	0x82
#define QUERY_DEV_CAP_AUX_ENTRY_SZ_OFFSET	0x84
#define QUERY_DEV_CAP_ALTC_ENTRY_SZ_OFFSET	0x86
#define QUERY_DEV_CAP_EQC_ENTRY_SZ_OFFSET	0x88
#define QUERY_DEV_CAP_CQC_ENTRY_SZ_OFFSET	0x8a
#define QUERY_DEV_CAP_SRQ_ENTRY_SZ_OFFSET	0x8c
#define QUERY_DEV_CAP_C_MPT_ENTRY_SZ_OFFSET	0x8e
#define QUERY_DEV_CAP_MTT_ENTRY_SZ_OFFSET	0x90
#define QUERY_DEV_CAP_D_MPT_ENTRY_SZ_OFFSET	0x92
#define QUERY_DEV_CAP_BMME_FLAGS_OFFSET		0x94
#define QUERY_DEV_CAP_RSVD_LKEY_OFFSET		0x98
#define QUERY_DEV_CAP_MAX_ICM_SZ_OFFSET		0xa0
#define QUERY_DEV_CAP_FW_REASSIGN_MAC		0x9d

	dev_cap->flags2 = 0;
	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mlx4_cmd_box(dev, 0, mailbox->dma, 0, 0, MLX4_CMD_QUERY_DEV_CAP,
			   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	if (err)
		goto out;

	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_QP_OFFSET);
	dev_cap->reserved_qps = 1 << (field & 0xf);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_QP_OFFSET);
	dev_cap->max_qps = 1 << (field & 0x1f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_SRQ_OFFSET);
	dev_cap->reserved_srqs = 1 << (field >> 4);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_SRQ_OFFSET);
	dev_cap->max_srqs = 1 << (field & 0x1f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_CQ_SZ_OFFSET);
	dev_cap->max_cq_sz = 1 << field;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_CQ_OFFSET);
	dev_cap->reserved_cqs = 1 << (field & 0xf);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_CQ_OFFSET);
	dev_cap->max_cqs = 1 << (field & 0x1f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_MPT_OFFSET);
	dev_cap->max_mpts = 1 << (field & 0x3f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_EQ_OFFSET);
	dev_cap->reserved_eqs = field & 0xf;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_EQ_OFFSET);
	dev_cap->max_eqs = 1 << (field & 0xf);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_MTT_OFFSET);
	dev_cap->reserved_mtts = 1 << (field >> 4);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_MRW_SZ_OFFSET);
	dev_cap->max_mrw_sz = 1 << field;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_MRW_OFFSET);
	dev_cap->reserved_mrws = 1 << (field & 0xf);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_MTT_SEG_OFFSET);
	dev_cap->max_mtt_seg = 1 << (field & 0x3f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_REQ_QP_OFFSET);
	dev_cap->max_requester_per_qp = 1 << (field & 0x3f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_RES_QP_OFFSET);
	dev_cap->max_responder_per_qp = 1 << (field & 0x3f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_GSO_OFFSET);
	field &= 0x1f;
	if (!field)
		dev_cap->max_gso_sz = 0;
	else
		dev_cap->max_gso_sz = 1 << field;

	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSS_OFFSET);
	if (field & 0x20)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_RSS_XOR;
	if (field & 0x10)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_RSS_TOP;
	field &= 0xf;
	if (field) {
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_RSS;
		dev_cap->max_rss_tbl_sz = 1 << field;
	} else
		dev_cap->max_rss_tbl_sz = 0;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_RDMA_OFFSET);
	dev_cap->max_rdma_global = 1 << (field & 0x3f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_ACK_DELAY_OFFSET);
	dev_cap->local_ca_ack_delay = field & 0x1f;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_VL_PORT_OFFSET);
	dev_cap->num_ports = field & 0xf;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_MSG_SZ_OFFSET);
	dev_cap->max_msg_sz = 1 << (field & 0x1f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET);
	if (field & 0x80)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_FS_EN;
	dev_cap->fs_log_max_ucast_qp_range_size = field & 0x1f;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_FLOW_STEERING_MAX_QP_OFFSET);
	dev_cap->fs_max_num_qp_per_entry = field;
	MLX4_GET(stat_rate, outbox, QUERY_DEV_CAP_RATE_SUPPORT_OFFSET);
	dev_cap->stat_rate_support = stat_rate;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET);
	if (field & 0x80)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_TS;
	MLX4_GET(ext_flags, outbox, QUERY_DEV_CAP_EXT_FLAGS_OFFSET);
	MLX4_GET(flags, outbox, QUERY_DEV_CAP_FLAGS_OFFSET);
	dev_cap->flags = flags | (u64)ext_flags << 32;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_UAR_OFFSET);
	dev_cap->reserved_uars = field >> 4;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_UAR_SZ_OFFSET);
	dev_cap->uar_size = 1 << ((field & 0x3f) + 20);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_PAGE_SZ_OFFSET);
	dev_cap->min_page_sz = 1 << field;

	MLX4_GET(field, outbox, QUERY_DEV_CAP_BF_OFFSET);
	if (field & 0x80) {
		MLX4_GET(field, outbox, QUERY_DEV_CAP_LOG_BF_REG_SZ_OFFSET);
		dev_cap->bf_reg_size = 1 << (field & 0x1f);
		MLX4_GET(field, outbox, QUERY_DEV_CAP_LOG_MAX_BF_REGS_PER_PAGE_OFFSET);
		if ((1 << (field & 0x3f)) > (PAGE_SIZE / dev_cap->bf_reg_size))
			field = 3;
		dev_cap->bf_regs_per_page = 1 << (field & 0x3f);
		mlx4_dbg(dev, "BlueFlame available (reg size %d, regs/page %d)\n",
			 dev_cap->bf_reg_size, dev_cap->bf_regs_per_page);
	} else {
		dev_cap->bf_reg_size = 0;
		mlx4_dbg(dev, "BlueFlame not available\n");
	}

	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_SG_SQ_OFFSET);
	dev_cap->max_sq_sg = field;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_MAX_DESC_SZ_SQ_OFFSET);
	dev_cap->max_sq_desc_sz = size;

	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_QP_MCG_OFFSET);
	dev_cap->max_qp_per_mcg = 1 << field;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_MCG_OFFSET);
	dev_cap->reserved_mgms = field & 0xf;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_MCG_OFFSET);
	dev_cap->max_mcgs = 1 << field;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_PD_OFFSET);
	dev_cap->reserved_pds = field >> 4;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_PD_OFFSET);
	dev_cap->max_pds = 1 << (field & 0x3f);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSVD_XRC_OFFSET);
	dev_cap->reserved_xrcds = field >> 4;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_XRC_OFFSET);
	dev_cap->max_xrcds = 1 << (field & 0x1f);

	MLX4_GET(size, outbox, QUERY_DEV_CAP_RDMARC_ENTRY_SZ_OFFSET);
	dev_cap->rdmarc_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_QPC_ENTRY_SZ_OFFSET);
	dev_cap->qpc_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_AUX_ENTRY_SZ_OFFSET);
	dev_cap->aux_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_ALTC_ENTRY_SZ_OFFSET);
	dev_cap->altc_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_EQC_ENTRY_SZ_OFFSET);
	dev_cap->eqc_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_CQC_ENTRY_SZ_OFFSET);
	dev_cap->cqc_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_SRQ_ENTRY_SZ_OFFSET);
	dev_cap->srq_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_C_MPT_ENTRY_SZ_OFFSET);
	dev_cap->cmpt_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_MTT_ENTRY_SZ_OFFSET);
	dev_cap->mtt_entry_sz = size;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_D_MPT_ENTRY_SZ_OFFSET);
	dev_cap->dmpt_entry_sz = size;

	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_SRQ_SZ_OFFSET);
	dev_cap->max_srq_sz = 1 << field;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_QP_SZ_OFFSET);
	dev_cap->max_qp_sz = 1 << field;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_RSZ_SRQ_OFFSET);
	dev_cap->resize_srq = field & 1;
	MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_SG_RQ_OFFSET);
	dev_cap->max_rq_sg = field;
	MLX4_GET(size, outbox, QUERY_DEV_CAP_MAX_DESC_SZ_RQ_OFFSET);
	dev_cap->max_rq_desc_sz = size;

	MLX4_GET(dev_cap->bmme_flags, outbox,
		 QUERY_DEV_CAP_BMME_FLAGS_OFFSET);
	MLX4_GET(dev_cap->reserved_lkey, outbox,
		 QUERY_DEV_CAP_RSVD_LKEY_OFFSET);
	MLX4_GET(field, outbox, QUERY_DEV_CAP_FW_REASSIGN_MAC);
	if (field & 1<<6)
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAGS2_REASSIGN_MAC_EN;
	MLX4_GET(dev_cap->max_icm_sz, outbox,
		 QUERY_DEV_CAP_MAX_ICM_SZ_OFFSET);
	if (dev_cap->flags & MLX4_DEV_CAP_FLAG_COUNTERS)
		MLX4_GET(dev_cap->max_counters, outbox,
			 QUERY_DEV_CAP_MAX_COUNTERS_OFFSET);

	MLX4_GET(field32, outbox, QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET);
	if (field32 & (1 << 16))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_UPDATE_QP;
	if (field32 & (1 << 26))
		dev_cap->flags2 |= MLX4_DEV_CAP_FLAG2_VLAN_CONTROL;

	if (dev->flags & MLX4_FLAG_OLD_PORT_CMDS) {
		for (i = 1; i <= dev_cap->num_ports; ++i) {
			MLX4_GET(field, outbox, QUERY_DEV_CAP_VL_PORT_OFFSET);
			dev_cap->max_vl[i]	   = field >> 4;
			MLX4_GET(field, outbox, QUERY_DEV_CAP_MTU_WIDTH_OFFSET);
			dev_cap->ib_mtu[i]	   = field >> 4;
			dev_cap->max_port_width[i] = field & 0xf;
			MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_GID_OFFSET);
			dev_cap->max_gids[i]	   = 1 << (field & 0xf);
			MLX4_GET(field, outbox, QUERY_DEV_CAP_MAX_PKEY_OFFSET);
			dev_cap->max_pkeys[i]	   = 1 << (field & 0xf);
		}
	} else {
#define QUERY_PORT_SUPPORTED_TYPE_OFFSET	0x00
#define QUERY_PORT_MTU_OFFSET			0x01
#define QUERY_PORT_ETH_MTU_OFFSET		0x02
#define QUERY_PORT_WIDTH_OFFSET			0x06
#define QUERY_PORT_MAX_GID_PKEY_OFFSET		0x07
#define QUERY_PORT_MAX_MACVLAN_OFFSET		0x0a
#define QUERY_PORT_MAX_VL_OFFSET		0x0b
#define QUERY_PORT_MAC_OFFSET			0x10

		for (i = 1; i <= dev_cap->num_ports; ++i) {
			err = mlx4_cmd_box(dev, 0, mailbox->dma, i, 0, MLX4_CMD_QUERY_PORT,
					   MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
			if (err)
				goto out;

			MLX4_GET(field, outbox, QUERY_PORT_SUPPORTED_TYPE_OFFSET);
			dev_cap->supported_port_types[i] = field & 3;
			dev_cap->suggested_type[i] = (field >> 3) & 1;
			dev_cap->default_sense[i] = (field >> 4) & 1;
			MLX4_GET(field, outbox, QUERY_PORT_MTU_OFFSET);
			dev_cap->ib_mtu[i]	   = field & 0xf;
			MLX4_GET(field, outbox, QUERY_PORT_WIDTH_OFFSET);
			dev_cap->max_port_width[i] = field & 0xf;
			MLX4_GET(field, outbox, QUERY_PORT_MAX_GID_PKEY_OFFSET);
			dev_cap->max_gids[i]	   = 1 << (field >> 4);
			dev_cap->max_pkeys[i]	   = 1 << (field & 0xf);
			MLX4_GET(field, outbox, QUERY_PORT_MAX_VL_OFFSET);
			dev_cap->max_vl[i]	   = field & 0xf;
			MLX4_GET(field, outbox, QUERY_PORT_MAX_MACVLAN_OFFSET);
			dev_cap->log_max_macs[i]  = field & 0xf;
			dev_cap->log_max_vlans[i] = field >> 4;
			MLX4_GET(dev_cap->eth_mtu[i], outbox, QUERY_PORT_ETH_MTU_OFFSET);
			MLX4_GET(dev_cap->def_mac[i], outbox, QUERY_PORT_MAC_OFFSET);
		}
	}

	mlx4_dbg(dev, "Base MM extensions: flags %08x, rsvd L_Key %08x\n",
		 dev_cap->bmme_flags, dev_cap->reserved_lkey);

	/*
	 * Each UAR has 4 EQ doorbells; so if a UAR is reserved, then
	 * we can't use any EQs whose doorbell falls on that page,
	 * even if the EQ itself isn't reserved.
	 */
	dev_cap->reserved_eqs = max(dev_cap->reserved_uars * 4,
				    dev_cap->reserved_eqs);

	mlx4_dbg(dev, "Max ICM size %lld MB\n",
		 (unsigned long long) dev_cap->max_icm_sz >> 20);
	mlx4_dbg(dev, "Max QPs: %d, reserved QPs: %d, entry size: %d\n",
		 dev_cap->max_qps, dev_cap->reserved_qps, dev_cap->qpc_entry_sz);
	mlx4_dbg(dev, "Max SRQs: %d, reserved SRQs: %d, entry size: %d\n",
		 dev_cap->max_srqs, dev_cap->reserved_srqs, dev_cap->srq_entry_sz);
	mlx4_dbg(dev, "Max CQs: %d, reserved CQs: %d, entry size: %d\n",
		 dev_cap->max_cqs, dev_cap->reserved_cqs, dev_cap->cqc_entry_sz);
	mlx4_dbg(dev, "Max EQs: %d, reserved EQs: %d, entry size: %d\n",
		 dev_cap->max_eqs, dev_cap->reserved_eqs, dev_cap->eqc_entry_sz);
	mlx4_dbg(dev, "reserved MPTs: %d, reserved MTTs: %d\n",
		 dev_cap->reserved_mrws, dev_cap->reserved_mtts);
	mlx4_dbg(dev, "Max PDs: %d, reserved PDs: %d, reserved UARs: %d\n",
		 dev_cap->max_pds, dev_cap->reserved_pds, dev_cap->reserved_uars);
	mlx4_dbg(dev, "Max QP/MCG: %d, reserved MGMs: %d\n",
		 dev_cap->max_pds, dev_cap->reserved_mgms);
	mlx4_dbg(dev, "Max CQEs: %d, max WQEs: %d, max SRQ WQEs: %d\n",
		 dev_cap->max_cq_sz, dev_cap->max_qp_sz, dev_cap->max_srq_sz);
	mlx4_dbg(dev, "Local CA ACK delay: %d, max MTU: %d, port width cap: %d\n",
		 dev_cap->local_ca_ack_delay, 128 << dev_cap->ib_mtu[1],
		 dev_cap->max_port_width[1]);
	mlx4_dbg(dev, "Max SQ desc size: %d, max SQ S/G: %d\n",
		 dev_cap->max_sq_desc_sz, dev_cap->max_sq_sg);
	mlx4_dbg(dev, "Max RQ desc size: %d, max RQ S/G: %d\n",
		 dev_cap->max_rq_desc_sz, dev_cap->max_rq_sg);
	mlx4_dbg(dev, "Max GSO size: %d\n", dev_cap->max_gso_sz);
	mlx4_dbg(dev, "Max counters: %d\n", dev_cap->max_counters);
	mlx4_dbg(dev, "Max RSS Table size: %d\n", dev_cap->max_rss_tbl_sz);

	dump_dev_cap_flags(dev, dev_cap->flags);
	dump_dev_cap_flags2(dev, dev_cap->flags2);

out:
	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}