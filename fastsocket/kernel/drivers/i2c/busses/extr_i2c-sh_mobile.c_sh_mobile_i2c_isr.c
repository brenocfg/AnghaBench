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
struct sh_mobile_i2c_data {unsigned char sr; int /*<<< orphan*/  wait; TYPE_1__* msg; int /*<<< orphan*/  pos; int /*<<< orphan*/  dev; } ;
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int /*<<< orphan*/  ICSR (struct sh_mobile_i2c_data*) ; 
 unsigned char ICSR_AL ; 
 unsigned char ICSR_TACK ; 
 unsigned char ICSR_WAIT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned char SW_DONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char,unsigned char,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (unsigned char,int /*<<< orphan*/ ) ; 
 struct sh_mobile_i2c_data* platform_get_drvdata (struct platform_device*) ; 
 int sh_mobile_i2c_isr_rx (struct sh_mobile_i2c_data*) ; 
 int sh_mobile_i2c_isr_tx (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sh_mobile_i2c_isr(int irq, void *dev_id)
{
	struct platform_device *dev = dev_id;
	struct sh_mobile_i2c_data *pd = platform_get_drvdata(dev);
	unsigned char sr;
	int wakeup;

	sr = ioread8(ICSR(pd));
	pd->sr |= sr; /* remember state */

	dev_dbg(pd->dev, "i2c_isr 0x%02x 0x%02x %s %d %d!\n", sr, pd->sr,
	       (pd->msg->flags & I2C_M_RD) ? "read" : "write",
	       pd->pos, pd->msg->len);

	if (sr & (ICSR_AL | ICSR_TACK)) {
		/* don't interrupt transaction - continue to issue stop */
		iowrite8(sr & ~(ICSR_AL | ICSR_TACK), ICSR(pd));
		wakeup = 0;
	} else if (pd->msg->flags & I2C_M_RD)
		wakeup = sh_mobile_i2c_isr_rx(pd);
	else
		wakeup = sh_mobile_i2c_isr_tx(pd);

	if (sr & ICSR_WAIT) /* TODO: add delay here to support slow acks */
		iowrite8(sr & ~ICSR_WAIT, ICSR(pd));

	if (wakeup) {
		pd->sr |= SW_DONE;
		wake_up(&pd->wait);
	}

	return IRQ_HANDLED;
}