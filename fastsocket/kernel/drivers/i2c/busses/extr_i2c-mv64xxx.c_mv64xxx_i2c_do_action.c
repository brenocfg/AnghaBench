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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct mv64xxx_i2c_data {int action; int cntl_bits; int addr1; int addr2; int /*<<< orphan*/  waitq; int /*<<< orphan*/  block; scalar_t__ reg_base; int /*<<< orphan*/  rc; TYPE_2__ adapter; int /*<<< orphan*/  byte_posn; TYPE_1__* msg; } ;
struct TYPE_3__ {int* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
#define  MV64XXX_I2C_ACTION_CONTINUE 136 
#define  MV64XXX_I2C_ACTION_INVALID 135 
#define  MV64XXX_I2C_ACTION_RCV_DATA 134 
#define  MV64XXX_I2C_ACTION_RCV_DATA_STOP 133 
#define  MV64XXX_I2C_ACTION_SEND_ADDR_1 132 
#define  MV64XXX_I2C_ACTION_SEND_ADDR_2 131 
#define  MV64XXX_I2C_ACTION_SEND_DATA 130 
#define  MV64XXX_I2C_ACTION_SEND_START 129 
#define  MV64XXX_I2C_ACTION_SEND_STOP 128 
 scalar_t__ MV64XXX_I2C_REG_CONTROL ; 
 int MV64XXX_I2C_REG_CONTROL_INTEN ; 
 int MV64XXX_I2C_REG_CONTROL_START ; 
 int MV64XXX_I2C_REG_CONTROL_STOP ; 
 scalar_t__ MV64XXX_I2C_REG_DATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void
mv64xxx_i2c_do_action(struct mv64xxx_i2c_data *drv_data)
{
	switch(drv_data->action) {
	case MV64XXX_I2C_ACTION_CONTINUE:
		writel(drv_data->cntl_bits,
			drv_data->reg_base + MV64XXX_I2C_REG_CONTROL);
		break;

	case MV64XXX_I2C_ACTION_SEND_START:
		writel(drv_data->cntl_bits | MV64XXX_I2C_REG_CONTROL_START,
			drv_data->reg_base + MV64XXX_I2C_REG_CONTROL);
		break;

	case MV64XXX_I2C_ACTION_SEND_ADDR_1:
		writel(drv_data->addr1,
			drv_data->reg_base + MV64XXX_I2C_REG_DATA);
		writel(drv_data->cntl_bits,
			drv_data->reg_base + MV64XXX_I2C_REG_CONTROL);
		break;

	case MV64XXX_I2C_ACTION_SEND_ADDR_2:
		writel(drv_data->addr2,
			drv_data->reg_base + MV64XXX_I2C_REG_DATA);
		writel(drv_data->cntl_bits,
			drv_data->reg_base + MV64XXX_I2C_REG_CONTROL);
		break;

	case MV64XXX_I2C_ACTION_SEND_DATA:
		writel(drv_data->msg->buf[drv_data->byte_posn++],
			drv_data->reg_base + MV64XXX_I2C_REG_DATA);
		writel(drv_data->cntl_bits,
			drv_data->reg_base + MV64XXX_I2C_REG_CONTROL);
		break;

	case MV64XXX_I2C_ACTION_RCV_DATA:
		drv_data->msg->buf[drv_data->byte_posn++] =
			readl(drv_data->reg_base + MV64XXX_I2C_REG_DATA);
		writel(drv_data->cntl_bits,
			drv_data->reg_base + MV64XXX_I2C_REG_CONTROL);
		break;

	case MV64XXX_I2C_ACTION_RCV_DATA_STOP:
		drv_data->msg->buf[drv_data->byte_posn++] =
			readl(drv_data->reg_base + MV64XXX_I2C_REG_DATA);
		drv_data->cntl_bits &= ~MV64XXX_I2C_REG_CONTROL_INTEN;
		writel(drv_data->cntl_bits | MV64XXX_I2C_REG_CONTROL_STOP,
			drv_data->reg_base + MV64XXX_I2C_REG_CONTROL);
		drv_data->block = 0;
		wake_up_interruptible(&drv_data->waitq);
		break;

	case MV64XXX_I2C_ACTION_INVALID:
	default:
		dev_err(&drv_data->adapter.dev,
			"mv64xxx_i2c_do_action: Invalid action: %d\n",
			drv_data->action);
		drv_data->rc = -EIO;
		/* FALLTHRU */
	case MV64XXX_I2C_ACTION_SEND_STOP:
		drv_data->cntl_bits &= ~MV64XXX_I2C_REG_CONTROL_INTEN;
		writel(drv_data->cntl_bits | MV64XXX_I2C_REG_CONTROL_STOP,
			drv_data->reg_base + MV64XXX_I2C_REG_CONTROL);
		drv_data->block = 0;
		wake_up_interruptible(&drv_data->waitq);
		break;
	}
}