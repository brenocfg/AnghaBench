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
typedef  int u8 ;
typedef  int u32 ;
struct mlx4_vhcr {int op_modifier; int in_modifier; } ;
struct TYPE_4__ {int num_ports; int function_caps; int num_qps; int num_srqs; int num_cqs; int num_eqs; int reserved_eqs; int num_mpts; int num_mtts; int num_mgms; int num_amgms; } ;
struct TYPE_3__ {int base_tunnel_sqpn; int base_proxy_sqpn; } ;
struct mlx4_dev {TYPE_2__ caps; TYPE_1__ phys_caps; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  buf; } ;
struct mlx4_cmd_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX4_PUT (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_CQ_QUOTA_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_ETH_PROPS_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_FLAGS_OFFSET ; 
 int QUERY_FUNC_CAP_FLAG_ETH ; 
 int QUERY_FUNC_CAP_FLAG_RDMA ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_FMR_OFFSET ; 
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
 int /*<<< orphan*/  QUERY_FUNC_CAP_RDMA_PROPS_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_RESERVED_EQ_OFFSET ; 
 int /*<<< orphan*/  QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET ; 

int mlx4_QUERY_FUNC_CAP_wrapper(struct mlx4_dev *dev, int slave,
				struct mlx4_vhcr *vhcr,
				struct mlx4_cmd_mailbox *inbox,
				struct mlx4_cmd_mailbox *outbox,
				struct mlx4_cmd_info *cmd)
{
	u8	field;
	u32	size;
	int	err = 0;

#define QUERY_FUNC_CAP_FLAGS_OFFSET		0x0
#define QUERY_FUNC_CAP_NUM_PORTS_OFFSET		0x1
#define QUERY_FUNC_CAP_PF_BHVR_OFFSET		0x4
#define QUERY_FUNC_CAP_FMR_OFFSET		0x8
#define QUERY_FUNC_CAP_QP_QUOTA_OFFSET		0x10
#define QUERY_FUNC_CAP_CQ_QUOTA_OFFSET		0x14
#define QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET		0x18
#define QUERY_FUNC_CAP_MPT_QUOTA_OFFSET		0x20
#define QUERY_FUNC_CAP_MTT_QUOTA_OFFSET		0x24
#define QUERY_FUNC_CAP_MCG_QUOTA_OFFSET		0x28
#define QUERY_FUNC_CAP_MAX_EQ_OFFSET		0x2c
#define QUERY_FUNC_CAP_RESERVED_EQ_OFFSET	0x30

#define QUERY_FUNC_CAP_FMR_FLAG			0x80
#define QUERY_FUNC_CAP_FLAG_RDMA		0x40
#define QUERY_FUNC_CAP_FLAG_ETH			0x80

/* when opcode modifier = 1 */
#define QUERY_FUNC_CAP_PHYS_PORT_OFFSET		0x3
#define QUERY_FUNC_CAP_RDMA_PROPS_OFFSET	0x8
#define QUERY_FUNC_CAP_ETH_PROPS_OFFSET		0xc

#define QUERY_FUNC_CAP_QP0_TUNNEL		0x10
#define QUERY_FUNC_CAP_QP0_PROXY		0x14
#define QUERY_FUNC_CAP_QP1_TUNNEL		0x18
#define QUERY_FUNC_CAP_QP1_PROXY		0x1c

#define QUERY_FUNC_CAP_ETH_PROPS_FORCE_MAC	0x40
#define QUERY_FUNC_CAP_ETH_PROPS_FORCE_VLAN	0x80

#define QUERY_FUNC_CAP_RDMA_PROPS_FORCE_PHY_WQE_GID 0x80

	if (vhcr->op_modifier == 1) {
		field = 0;
		/* ensure force vlan and force mac bits are not set */
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_ETH_PROPS_OFFSET);
		/* ensure that phy_wqe_gid bit is not set */
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_RDMA_PROPS_OFFSET);

		field = vhcr->in_modifier; /* phys-port = logical-port */
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_PHYS_PORT_OFFSET);

		/* size is now the QP number */
		size = dev->phys_caps.base_tunnel_sqpn + 8 * slave + field - 1;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP0_TUNNEL);

		size += 2;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP1_TUNNEL);

		size = dev->phys_caps.base_proxy_sqpn + 8 * slave + field - 1;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP0_PROXY);

		size += 2;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP1_PROXY);

	} else if (vhcr->op_modifier == 0) {
		/* enable rdma and ethernet interfaces */
		field = (QUERY_FUNC_CAP_FLAG_ETH | QUERY_FUNC_CAP_FLAG_RDMA);
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_FLAGS_OFFSET);

		field = dev->caps.num_ports;
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_NUM_PORTS_OFFSET);

		size = dev->caps.function_caps; /* set PF behaviours */
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_PF_BHVR_OFFSET);

		field = 0; /* protected FMR support not available as yet */
		MLX4_PUT(outbox->buf, field, QUERY_FUNC_CAP_FMR_OFFSET);

		size = dev->caps.num_qps;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_QP_QUOTA_OFFSET);

		size = dev->caps.num_srqs;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_SRQ_QUOTA_OFFSET);

		size = dev->caps.num_cqs;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_CQ_QUOTA_OFFSET);

		size = dev->caps.num_eqs;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MAX_EQ_OFFSET);

		size = dev->caps.reserved_eqs;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_RESERVED_EQ_OFFSET);

		size = dev->caps.num_mpts;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MPT_QUOTA_OFFSET);

		size = dev->caps.num_mtts;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MTT_QUOTA_OFFSET);

		size = dev->caps.num_mgms + dev->caps.num_amgms;
		MLX4_PUT(outbox->buf, size, QUERY_FUNC_CAP_MCG_QUOTA_OFFSET);

	} else
		err = -EINVAL;

	return err;
}