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
typedef  int u8 ;
typedef  int u32 ;
struct mlx4_func_cap {int flags; int num_ports; int pf_context_behaviour; int qp_quota; int srq_quota; int cq_quota; int max_eq; int reserved_eq; int mpt_quota; int mtt_quota; int mcg_quota; int physical_port; int qp0_tunnel_qpn; int qp0_proxy_qpn; int qp1_tunnel_qpn; int qp1_proxy_qpn; } ;
struct TYPE_2__ {int num_ports; scalar_t__* port_type; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int* buf; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int EPROTONOSUPPORT ; 
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_QUERY_FUNC_CAP ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int /*<<< orphan*/  MLX4_GET (int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX4_PORT_TYPE_ETH ; 
 scalar_t__ MLX4_PORT_TYPE_IB ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_CQ_QUOTA_OFFSET ; 
 int QUERY_FUNC_CAP_ETH_PROPS_FORCE_MAC ; 
 int QUERY_FUNC_CAP_ETH_PROPS_FORCE_VLAN ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_ETH_PROPS_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_FLAGS_OFFSET ; 
 int QUERY_FUNC_CAP_FLAG_ETH ; 
 int QUERY_FUNC_CAP_FLAG_RDMA ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_MAX_EQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_MCG_QUOTA_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_MPT_QUOTA_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_MTT_QUOTA_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_NUM_PORTS_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_PF_BHVR_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_PHYS_PORT_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_QP0_PROXY ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_QP0_TUNNEL ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_QP1_PROXY ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_QP1_TUNNEL ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_QP_QUOTA_OFFSET ; 
 int QUERY_FUNC_CAP_RDMA_PROPS_FORCE_PHY_WQE_GID ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_RDMA_PROPS_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_RESERVED_EQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_QUERY_FUNC_CAP(struct mlx4_dev *dev, u32 gen_or_port,
			struct mlx4_func_cap *func_cap)
{
	struct mlx4_cmd_mailbox *mailbox;
	u32			*outbox;
	u8			field, op_modifier;
	u32			size;
	int			err = 0;

	op_modifier = !!gen_or_port; /* 0 = general, 1 = logical port */

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	err = mlx4_cmd_box(dev, 0, mailbox->dma, gen_or_port, op_modifier,
			   MLX4_CMD_QUERY_FUNC_CAP,
			   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
	if (err)
		goto out;

	outbox = mailbox->buf;

	if (!op_modifier) {
		MLX4_GET(field, outbox, QUERY_FUNC_CAP_FLAGS_OFFSET);
		if (!(field & (QUERY_FUNC_CAP_FLAG_ETH | QUERY_FUNC_CAP_FLAG_RDMA))) {
			mlx4_err(dev, "The host supports neither eth nor rdma interfaces\n");
			err = -EPROTONOSUPPORT;
			goto out;
		}
		func_cap->flags = field;

		MLX4_GET(field, outbox, QUERY_FUNC_CAP_NUM_PORTS_OFFSET);
		func_cap->num_ports = field;

		MLX4_GET(size, outbox, QUERY_FUNC_CAP_PF_BHVR_OFFSET);
		func_cap->pf_context_behaviour = size;

		MLX4_GET(size, outbox, QUERY_FUNC_CAP_QP_QUOTA_OFFSET);
		func_cap->qp_quota = size & 0xFFFFFF;

		MLX4_GET(size, outbox, QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET);
		func_cap->srq_quota = size & 0xFFFFFF;

		MLX4_GET(size, outbox, QUERY_FUNC_CAP_CQ_QUOTA_OFFSET);
		func_cap->cq_quota = size & 0xFFFFFF;

		MLX4_GET(size, outbox, QUERY_FUNC_CAP_MAX_EQ_OFFSET);
		func_cap->max_eq = size & 0xFFFFFF;

		MLX4_GET(size, outbox, QUERY_FUNC_CAP_RESERVED_EQ_OFFSET);
		func_cap->reserved_eq = size & 0xFFFFFF;

		MLX4_GET(size, outbox, QUERY_FUNC_CAP_MPT_QUOTA_OFFSET);
		func_cap->mpt_quota = size & 0xFFFFFF;

		MLX4_GET(size, outbox, QUERY_FUNC_CAP_MTT_QUOTA_OFFSET);
		func_cap->mtt_quota = size & 0xFFFFFF;

		MLX4_GET(size, outbox, QUERY_FUNC_CAP_MCG_QUOTA_OFFSET);
		func_cap->mcg_quota = size & 0xFFFFFF;
		goto out;
	}

	/* logical port query */
	if (gen_or_port > dev->caps.num_ports) {
		err = -EINVAL;
		goto out;
	}

	if (dev->caps.port_type[gen_or_port] == MLX4_PORT_TYPE_ETH) {
		MLX4_GET(field, outbox, QUERY_FUNC_CAP_ETH_PROPS_OFFSET);
		if (field & QUERY_FUNC_CAP_ETH_PROPS_FORCE_VLAN) {
			mlx4_err(dev, "VLAN is enforced on this port\n");
			err = -EPROTONOSUPPORT;
			goto out;
		}

		if (field & QUERY_FUNC_CAP_ETH_PROPS_FORCE_MAC) {
			mlx4_err(dev, "Force mac is enabled on this port\n");
			err = -EPROTONOSUPPORT;
			goto out;
		}
	} else if (dev->caps.port_type[gen_or_port] == MLX4_PORT_TYPE_IB) {
		MLX4_GET(field, outbox, QUERY_FUNC_CAP_RDMA_PROPS_OFFSET);
		if (field & QUERY_FUNC_CAP_RDMA_PROPS_FORCE_PHY_WQE_GID) {
			mlx4_err(dev, "phy_wqe_gid is "
				 "enforced on this ib port\n");
			err = -EPROTONOSUPPORT;
			goto out;
		}
	}

	MLX4_GET(field, outbox, QUERY_FUNC_CAP_PHYS_PORT_OFFSET);
	func_cap->physical_port = field;
	if (func_cap->physical_port != gen_or_port) {
		err = -ENOSYS;
		goto out;
	}

	MLX4_GET(size, outbox, QUERY_FUNC_CAP_QP0_TUNNEL);
	func_cap->qp0_tunnel_qpn = size & 0xFFFFFF;

	MLX4_GET(size, outbox, QUERY_FUNC_CAP_QP0_PROXY);
	func_cap->qp0_proxy_qpn = size & 0xFFFFFF;

	MLX4_GET(size, outbox, QUERY_FUNC_CAP_QP1_TUNNEL);
	func_cap->qp1_tunnel_qpn = size & 0xFFFFFF;

	MLX4_GET(size, outbox, QUERY_FUNC_CAP_QP1_PROXY);
	func_cap->qp1_proxy_qpn = size & 0xFFFFFF;

	/* All other resources are allocated by the master, but we still report
	 * 'num' and 'reserved' capabilities as follows:
	 * - num remains the maximum resource index
	 * - 'num - reserved' is the total available objects of a resource, but
	 *   resource indices may be less than 'reserved'
	 * TODO: set per-resource quotas */

out:
	mlx4_free_cmd_mailbox(dev, mailbox);

	return err;
}