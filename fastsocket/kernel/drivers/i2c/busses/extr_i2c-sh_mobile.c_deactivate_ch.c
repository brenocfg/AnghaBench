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
struct sh_mobile_i2c_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICCR (struct sh_mobile_i2c_data*) ; 
 int ICCR_ICE ; 
 int /*<<< orphan*/  ICIC (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  ICSR (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void deactivate_ch(struct sh_mobile_i2c_data *pd)
{
	/* Clear/disable interrupts */
	iowrite8(0, ICSR(pd));
	iowrite8(0, ICIC(pd));

	/* Disable channel */
	iowrite8(ioread8(ICCR(pd)) & ~ICCR_ICE, ICCR(pd));

	/* Disable clock and mark device as idle */
	clk_disable(pd->clk);
	pm_runtime_put_sync(pd->dev);
}