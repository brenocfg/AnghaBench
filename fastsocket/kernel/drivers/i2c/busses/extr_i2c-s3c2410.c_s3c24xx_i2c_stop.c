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
struct s3c24xx_i2c {int /*<<< orphan*/  state; scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ S3C2410_IICSTAT ; 
 unsigned long S3C2410_IICSTAT_START ; 
 int /*<<< orphan*/  STATE_STOP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  s3c24xx_i2c_disable_irq (struct s3c24xx_i2c*) ; 
 int /*<<< orphan*/  s3c24xx_i2c_master_complete (struct s3c24xx_i2c*,int) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void s3c24xx_i2c_stop(struct s3c24xx_i2c *i2c, int ret)
{
	unsigned long iicstat = readl(i2c->regs + S3C2410_IICSTAT);

	dev_dbg(i2c->dev, "STOP\n");

	/* stop the transfer */
	iicstat &= ~S3C2410_IICSTAT_START;
	writel(iicstat, i2c->regs + S3C2410_IICSTAT);

	i2c->state = STATE_STOP;

	s3c24xx_i2c_master_complete(i2c, ret);
	s3c24xx_i2c_disable_irq(i2c);
}