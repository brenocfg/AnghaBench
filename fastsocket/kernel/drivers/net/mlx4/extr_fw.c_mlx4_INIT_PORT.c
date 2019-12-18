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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int* vl_cap; int* port_width_cap; int* ib_mtu_cap; int* gid_table_len; int* pkey_table_len; } ;
struct mlx4_dev {int flags; TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int* buf; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_PORT_FLAGS_OFFSET ; 
 int /*<<< orphan*/  INIT_PORT_IN_SIZE ; 
 int /*<<< orphan*/  INIT_PORT_MAX_GID_OFFSET ; 
 int /*<<< orphan*/  INIT_PORT_MAX_PKEY_OFFSET ; 
 int /*<<< orphan*/  INIT_PORT_MTU_OFFSET ; 
 int INIT_PORT_PORT_WIDTH_SHIFT ; 
 int INIT_PORT_VL_SHIFT ; 
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_INIT_PORT ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int MLX4_FLAG_OLD_PORT_CMDS ; 
 int /*<<< orphan*/  MLX4_PUT (int*,int,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd (struct mlx4_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_INIT_PORT(struct mlx4_dev *dev, int port)
{
	struct mlx4_cmd_mailbox *mailbox;
	u32 *inbox;
	int err;
	u32 flags;
	u16 field;

	if (dev->flags & MLX4_FLAG_OLD_PORT_CMDS) {
#define INIT_PORT_IN_SIZE          256
#define INIT_PORT_FLAGS_OFFSET     0x00
#define INIT_PORT_FLAG_SIG         (1 << 18)
#define INIT_PORT_FLAG_NG          (1 << 17)
#define INIT_PORT_FLAG_G0          (1 << 16)
#define INIT_PORT_VL_SHIFT         4
#define INIT_PORT_PORT_WIDTH_SHIFT 8
#define INIT_PORT_MTU_OFFSET       0x04
#define INIT_PORT_MAX_GID_OFFSET   0x06
#define INIT_PORT_MAX_PKEY_OFFSET  0x0a
#define INIT_PORT_GUID0_OFFSET     0x10
#define INIT_PORT_NODE_GUID_OFFSET 0x18
#define INIT_PORT_SI_GUID_OFFSET   0x20

		mailbox = mlx4_alloc_cmd_mailbox(dev);
		if (IS_ERR(mailbox))
			return PTR_ERR(mailbox);
		inbox = mailbox->buf;

		memset(inbox, 0, INIT_PORT_IN_SIZE);

		flags = 0;
		flags |= (dev->caps.vl_cap[port] & 0xf) << INIT_PORT_VL_SHIFT;
		flags |= (dev->caps.port_width_cap[port] & 0xf) << INIT_PORT_PORT_WIDTH_SHIFT;
		MLX4_PUT(inbox, flags,		  INIT_PORT_FLAGS_OFFSET);

		field = 128 << dev->caps.ib_mtu_cap[port];
		MLX4_PUT(inbox, field, INIT_PORT_MTU_OFFSET);
		field = dev->caps.gid_table_len[port];
		MLX4_PUT(inbox, field, INIT_PORT_MAX_GID_OFFSET);
		field = dev->caps.pkey_table_len[port];
		MLX4_PUT(inbox, field, INIT_PORT_MAX_PKEY_OFFSET);

		err = mlx4_cmd(dev, mailbox->dma, port, 0, MLX4_CMD_INIT_PORT,
			       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);

		mlx4_free_cmd_mailbox(dev, mailbox);
	} else
		err = mlx4_cmd(dev, 0, port, 0, MLX4_CMD_INIT_PORT,
			       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);

	return err;
}