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
struct sh_mobile_i2c_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
typedef  enum sh_mobile_i2c_op { ____Placeholder_sh_mobile_i2c_op } sh_mobile_i2c_op ;

/* Variables and functions */
 int /*<<< orphan*/  ICCR (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  ICDR (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  ICIC (struct sh_mobile_i2c_data*) ; 
 int ICIC_ALE ; 
 int ICIC_DTEE ; 
 int ICIC_TACKE ; 
 int ICIC_WAITE ; 
#define  OP_RX 135 
#define  OP_RX_STOP 134 
#define  OP_RX_STOP_DATA 133 
#define  OP_START 132 
#define  OP_TX 131 
#define  OP_TX_FIRST 130 
#define  OP_TX_STOP 129 
#define  OP_TX_TO_RX 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned char) ; 
 unsigned char ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned char i2c_op(struct sh_mobile_i2c_data *pd,
			    enum sh_mobile_i2c_op op, unsigned char data)
{
	unsigned char ret = 0;
	unsigned long flags;

	dev_dbg(pd->dev, "op %d, data in 0x%02x\n", op, data);

	spin_lock_irqsave(&pd->lock, flags);

	switch (op) {
	case OP_START: /* issue start and trigger DTE interrupt */
		iowrite8(0x94, ICCR(pd));
		break;
	case OP_TX_FIRST: /* disable DTE interrupt and write data */
		iowrite8(ICIC_WAITE | ICIC_ALE | ICIC_TACKE, ICIC(pd));
		iowrite8(data, ICDR(pd));
		break;
	case OP_TX: /* write data */
		iowrite8(data, ICDR(pd));
		break;
	case OP_TX_STOP: /* write data and issue a stop afterwards */
		iowrite8(data, ICDR(pd));
		iowrite8(0x90, ICCR(pd));
		break;
	case OP_TX_TO_RX: /* select read mode */
		iowrite8(0x81, ICCR(pd));
		break;
	case OP_RX: /* just read data */
		ret = ioread8(ICDR(pd));
		break;
	case OP_RX_STOP: /* enable DTE interrupt, issue stop */
		iowrite8(ICIC_DTEE | ICIC_WAITE | ICIC_ALE | ICIC_TACKE,
			 ICIC(pd));
		iowrite8(0xc0, ICCR(pd));
		break;
	case OP_RX_STOP_DATA: /* enable DTE interrupt, read data, issue stop */
		iowrite8(ICIC_DTEE | ICIC_WAITE | ICIC_ALE | ICIC_TACKE,
			 ICIC(pd));
		ret = ioread8(ICDR(pd));
		iowrite8(0xc0, ICCR(pd));
		break;
	}

	spin_unlock_irqrestore(&pd->lock, flags);

	dev_dbg(pd->dev, "op %d, data out 0x%02x\n", op, ret);
	return ret;
}