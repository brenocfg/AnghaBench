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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct pxa_i2c {int slave_addr; TYPE_1__ adap; scalar_t__ fast_mode; } ;

/* Variables and functions */
 int I2C_ICR_INIT ; 
 int I2C_ISR_INIT ; 
 int ICR_ALDIE ; 
 int ICR_FM ; 
 int ICR_IUE ; 
 int ICR_SADIE ; 
 int ICR_SSDIE ; 
 int ICR_UR ; 
 int /*<<< orphan*/  _ICR (struct pxa_i2c*) ; 
 int /*<<< orphan*/  _ISAR (struct pxa_i2c*) ; 
 int /*<<< orphan*/  _ISR (struct pxa_i2c*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_pxa_abort (struct pxa_i2c*) ; 
 int /*<<< orphan*/  i2c_pxa_set_slave (struct pxa_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2c_pxa_reset(struct pxa_i2c *i2c)
{
	pr_debug("Resetting I2C Controller Unit\n");

	/* abort any transfer currently under way */
	i2c_pxa_abort(i2c);

	/* reset according to 9.8 */
	writel(ICR_UR, _ICR(i2c));
	writel(I2C_ISR_INIT, _ISR(i2c));
	writel(readl(_ICR(i2c)) & ~ICR_UR, _ICR(i2c));

	writel(i2c->slave_addr, _ISAR(i2c));

	/* set control register values */
	writel(I2C_ICR_INIT | (i2c->fast_mode ? ICR_FM : 0), _ICR(i2c));

#ifdef CONFIG_I2C_PXA_SLAVE
	dev_info(&i2c->adap.dev, "Enabling slave mode\n");
	writel(readl(_ICR(i2c)) | ICR_SADIE | ICR_ALDIE | ICR_SSDIE, _ICR(i2c));
#endif

	i2c_pxa_set_slave(i2c, 0);

	/* enable unit */
	writel(readl(_ICR(i2c)) | ICR_IUE, _ICR(i2c));
	udelay(100);
}