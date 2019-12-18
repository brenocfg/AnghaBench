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
struct platform_device {int dummy; } ;
struct bfin_twi_iface {int saved_control; int /*<<< orphan*/  irq; int /*<<< orphan*/  saved_clkdiv; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int TWI_ENA ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bfin_twi_iface*) ; 
 struct bfin_twi_iface* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  read_CLKDIV (struct bfin_twi_iface*) ; 
 int read_CONTROL (struct bfin_twi_iface*) ; 
 int /*<<< orphan*/  write_CONTROL (struct bfin_twi_iface*,int) ; 

__attribute__((used)) static int i2c_bfin_twi_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct bfin_twi_iface *iface = platform_get_drvdata(pdev);

	iface->saved_clkdiv = read_CLKDIV(iface);
	iface->saved_control = read_CONTROL(iface);

	free_irq(iface->irq, iface);

	/* Disable TWI */
	write_CONTROL(iface, iface->saved_control & ~TWI_ENA);

	return 0;
}