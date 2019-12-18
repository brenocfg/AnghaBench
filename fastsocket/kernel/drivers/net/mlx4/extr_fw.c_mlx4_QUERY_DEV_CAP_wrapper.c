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
typedef  int u64 ;
typedef  int u32 ;
struct mlx4_vhcr {int dummy; } ;
struct TYPE_2__ {scalar_t__ steering_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {struct mlx4_cmd_mailbox* buf; int /*<<< orphan*/  dma; } ;
struct mlx4_cmd_info {int dummy; } ;

/* Variables and functions */
 int MLX4_BMME_FLAG_TYPE_2_WIN ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_QUERY_DEV_CAP ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int MLX4_DEV_CAP_FLAG_MEM_WINDOW ; 
 int MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV ; 
 int /*<<< orphan*/  MLX4_GET (int,struct mlx4_cmd_mailbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX4_PUT (struct mlx4_cmd_mailbox*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_BF_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_BMME_FLAGS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_EXT_FLAGS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx4_QUERY_DEV_CAP_wrapper(struct mlx4_dev *dev, int slave,
			       struct mlx4_vhcr *vhcr,
			       struct mlx4_cmd_mailbox *inbox,
			       struct mlx4_cmd_mailbox *outbox,
			       struct mlx4_cmd_info *cmd)
{
	u64	flags;
	int	err = 0;
	u8	field;
	u32	bmme_flags;

	err = mlx4_cmd_box(dev, 0, outbox->dma, 0, 0, MLX4_CMD_QUERY_DEV_CAP,
			   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	if (err)
		return err;

	/* add port mng change event capability and disable mw type 1
	 * unconditionally to slaves
	 */
	MLX4_GET(flags, outbox->buf, QUERY_DEV_CAP_EXT_FLAGS_OFFSET);
	flags |= MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV;
	flags &= ~MLX4_DEV_CAP_FLAG_MEM_WINDOW;
	MLX4_PUT(outbox->buf, flags, QUERY_DEV_CAP_EXT_FLAGS_OFFSET);

	/* For guests, disable timestamp */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET);
	field &= 0x7f;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET);

	/* For guests, report Blueflame disabled */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_BF_OFFSET);
	field &= 0x7f;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_BF_OFFSET);

	/* For guests, disable mw type 2 */
	MLX4_GET(bmme_flags, outbox, QUERY_DEV_CAP_BMME_FLAGS_OFFSET);
	bmme_flags &= ~MLX4_BMME_FLAG_TYPE_2_WIN;
	MLX4_PUT(outbox->buf, bmme_flags, QUERY_DEV_CAP_BMME_FLAGS_OFFSET);

	/* turn off device-managed steering capability if not enabled */
	if (dev->caps.steering_mode != MLX4_STEERING_MODE_DEVICE_MANAGED) {
		MLX4_GET(field, outbox->buf,
			 QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET);
		field &= 0x7f;
		MLX4_PUT(outbox->buf, field,
			 QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET);
	}
	return 0;
}