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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct mlx4_fw {int catas_offset; int catas_size; int catas_bar; int fw_pages; int clr_int_base; int clr_int_bar; int comm_base; int comm_bar; int clock_offset; int clock_bar; } ;
struct TYPE_3__ {int fw_ver; int function; } ;
struct mlx4_dev {TYPE_1__ caps; int /*<<< orphan*/  flags; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; int /*<<< orphan*/ * buf; } ;
struct mlx4_cmd {int max_cmds; } ;
struct TYPE_4__ {struct mlx4_cmd cmd; struct mlx4_fw fw; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_QUERY_FW ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 scalar_t__ MLX4_COMMAND_INTERFACE_MAX_REV ; 
 scalar_t__ MLX4_COMMAND_INTERFACE_MIN_REV ; 
 scalar_t__ MLX4_COMMAND_INTERFACE_NEW_PORT_CMDS ; 
 int /*<<< orphan*/  MLX4_FLAG_OLD_PORT_CMDS ; 
 int /*<<< orphan*/  MLX4_GET (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX4_ICM_PAGE_SHIFT ; 
 int MLX4_ICM_PAGE_SIZE ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  QUERY_FW_CLOCK_BAR ; 
 int /*<<< orphan*/  QUERY_FW_CLOCK_OFFSET ; 
 int /*<<< orphan*/  QUERY_FW_CLR_INT_BAR_OFFSET ; 
 int /*<<< orphan*/  QUERY_FW_CLR_INT_BASE_OFFSET ; 
 int /*<<< orphan*/  QUERY_FW_CMD_IF_REV_OFFSET ; 
 int /*<<< orphan*/  QUERY_FW_COMM_BAR_OFFSET ; 
 int /*<<< orphan*/  QUERY_FW_COMM_BASE_OFFSET ; 
 int /*<<< orphan*/  QUERY_FW_ERR_BAR_OFFSET ; 
 int /*<<< orphan*/  QUERY_FW_ERR_SIZE_OFFSET ; 
 int /*<<< orphan*/  QUERY_FW_ERR_START_OFFSET ; 
 int /*<<< orphan*/  QUERY_FW_MAX_CMD_OFFSET ; 
 int /*<<< orphan*/  QUERY_FW_PPF_ID ; 
 int /*<<< orphan*/  QUERY_FW_SIZE_OFFSET ; 
 int /*<<< orphan*/  QUERY_FW_VER_OFFSET ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_QUERY_FW(struct mlx4_dev *dev)
{
	struct mlx4_fw  *fw  = &mlx4_priv(dev)->fw;
	struct mlx4_cmd *cmd = &mlx4_priv(dev)->cmd;
	struct mlx4_cmd_mailbox *mailbox;
	u32 *outbox;
	int err = 0;
	u64 fw_ver;
	u16 cmd_if_rev;
	u8 lg;

#define QUERY_FW_OUT_SIZE             0x100
#define QUERY_FW_VER_OFFSET            0x00
#define QUERY_FW_PPF_ID		       0x09
#define QUERY_FW_CMD_IF_REV_OFFSET     0x0a
#define QUERY_FW_MAX_CMD_OFFSET        0x0f
#define QUERY_FW_ERR_START_OFFSET      0x30
#define QUERY_FW_ERR_SIZE_OFFSET       0x38
#define QUERY_FW_ERR_BAR_OFFSET        0x3c

#define QUERY_FW_SIZE_OFFSET           0x00
#define QUERY_FW_CLR_INT_BASE_OFFSET   0x20
#define QUERY_FW_CLR_INT_BAR_OFFSET    0x28

#define QUERY_FW_COMM_BASE_OFFSET      0x40
#define QUERY_FW_COMM_BAR_OFFSET       0x48

#define QUERY_FW_CLOCK_OFFSET	       0x50
#define QUERY_FW_CLOCK_BAR	       0x58

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	outbox = mailbox->buf;

	err = mlx4_cmd_box(dev, 0, mailbox->dma, 0, 0, MLX4_CMD_QUERY_FW,
			    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	if (err)
		goto out;

	MLX4_GET(fw_ver, outbox, QUERY_FW_VER_OFFSET);
	/*
	 * FW subminor version is at more significant bits than minor
	 * version, so swap here.
	 */
	dev->caps.fw_ver = (fw_ver & 0xffff00000000ull) |
		((fw_ver & 0xffff0000ull) >> 16) |
		((fw_ver & 0x0000ffffull) << 16);

	MLX4_GET(lg, outbox, QUERY_FW_PPF_ID);
	dev->caps.function = lg;

	if (mlx4_is_slave(dev))
		goto out;


	MLX4_GET(cmd_if_rev, outbox, QUERY_FW_CMD_IF_REV_OFFSET);
	if (cmd_if_rev < MLX4_COMMAND_INTERFACE_MIN_REV ||
	    cmd_if_rev > MLX4_COMMAND_INTERFACE_MAX_REV) {
		mlx4_err(dev, "Installed FW has unsupported "
			 "command interface revision %d.\n",
			 cmd_if_rev);
		mlx4_err(dev, "(Installed FW version is %d.%d.%03d)\n",
			 (int) (dev->caps.fw_ver >> 32),
			 (int) (dev->caps.fw_ver >> 16) & 0xffff,
			 (int) dev->caps.fw_ver & 0xffff);
		mlx4_err(dev, "This driver version supports only revisions %d to %d.\n",
			 MLX4_COMMAND_INTERFACE_MIN_REV, MLX4_COMMAND_INTERFACE_MAX_REV);
		err = -ENODEV;
		goto out;
	}

	if (cmd_if_rev < MLX4_COMMAND_INTERFACE_NEW_PORT_CMDS)
		dev->flags |= MLX4_FLAG_OLD_PORT_CMDS;

	MLX4_GET(lg, outbox, QUERY_FW_MAX_CMD_OFFSET);
	cmd->max_cmds = 1 << lg;

	mlx4_dbg(dev, "FW version %d.%d.%03d (cmd intf rev %d), max commands %d\n",
		 (int) (dev->caps.fw_ver >> 32),
		 (int) (dev->caps.fw_ver >> 16) & 0xffff,
		 (int) dev->caps.fw_ver & 0xffff,
		 cmd_if_rev, cmd->max_cmds);

	MLX4_GET(fw->catas_offset, outbox, QUERY_FW_ERR_START_OFFSET);
	MLX4_GET(fw->catas_size,   outbox, QUERY_FW_ERR_SIZE_OFFSET);
	MLX4_GET(fw->catas_bar,    outbox, QUERY_FW_ERR_BAR_OFFSET);
	fw->catas_bar = (fw->catas_bar >> 6) * 2;

	mlx4_dbg(dev, "Catastrophic error buffer at 0x%llx, size 0x%x, BAR %d\n",
		 (unsigned long long) fw->catas_offset, fw->catas_size, fw->catas_bar);

	MLX4_GET(fw->fw_pages,     outbox, QUERY_FW_SIZE_OFFSET);
	MLX4_GET(fw->clr_int_base, outbox, QUERY_FW_CLR_INT_BASE_OFFSET);
	MLX4_GET(fw->clr_int_bar,  outbox, QUERY_FW_CLR_INT_BAR_OFFSET);
	fw->clr_int_bar = (fw->clr_int_bar >> 6) * 2;

	MLX4_GET(fw->comm_base, outbox, QUERY_FW_COMM_BASE_OFFSET);
	MLX4_GET(fw->comm_bar,  outbox, QUERY_FW_COMM_BAR_OFFSET);
	fw->comm_bar = (fw->comm_bar >> 6) * 2;
	mlx4_dbg(dev, "Communication vector bar:%d offset:0x%llx\n",
		 fw->comm_bar, fw->comm_base);
	mlx4_dbg(dev, "FW size %d KB\n", fw->fw_pages >> 2);

	MLX4_GET(fw->clock_offset, outbox, QUERY_FW_CLOCK_OFFSET);
	MLX4_GET(fw->clock_bar,    outbox, QUERY_FW_CLOCK_BAR);
	fw->clock_bar = (fw->clock_bar >> 6) * 2;
	mlx4_dbg(dev, "Internal clock bar:%d offset:0x%llx\n",
		 fw->clock_bar, fw->clock_offset);

	/*
	 * Round up number of system pages needed in case
	 * MLX4_ICM_PAGE_SIZE < PAGE_SIZE.
	 */
	fw->fw_pages =
		ALIGN(fw->fw_pages, PAGE_SIZE / MLX4_ICM_PAGE_SIZE) >>
		(PAGE_SHIFT - MLX4_ICM_PAGE_SHIFT);

	mlx4_dbg(dev, "Clear int @ %llx, BAR %d\n",
		 (unsigned long long) fw->clr_int_base, fw->clr_int_bar);

out:
	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}