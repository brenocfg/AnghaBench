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
struct device {int dummy; } ;
struct sdio_func {struct device dev; } ;
struct i2400ms {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2400MS_INTR_CLEAR_ADDR ; 
 int /*<<< orphan*/  I2400MS_INTR_STATUS_ADDR ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400ms*) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400ms*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  i2400ms_rx (struct i2400ms*) ; 
 struct i2400ms* sdio_get_drvdata (struct sdio_func*) ; 
 int sdio_readb (struct sdio_func*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdio_writeb (struct sdio_func*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static
void i2400ms_irq(struct sdio_func *func)
{
	int ret;
	struct i2400ms *i2400ms = sdio_get_drvdata(func);
	struct device *dev = &func->dev;
	int val;

	d_fnstart(6, dev, "(i2400ms %p)\n", i2400ms);
	val = sdio_readb(func, I2400MS_INTR_STATUS_ADDR, &ret);
	if (ret < 0) {
		dev_err(dev, "RX: Can't read interrupt status: %d\n", ret);
		goto error_no_irq;
	}
	if (!val) {
		dev_err(dev, "RX: BUG? got IRQ but no interrupt ready?\n");
		goto error_no_irq;
	}
	sdio_writeb(func, 1, I2400MS_INTR_CLEAR_ADDR, &ret);
	i2400ms_rx(i2400ms);
error_no_irq:
	d_fnend(6, dev, "(i2400ms %p) = void\n", i2400ms);
	return;
}