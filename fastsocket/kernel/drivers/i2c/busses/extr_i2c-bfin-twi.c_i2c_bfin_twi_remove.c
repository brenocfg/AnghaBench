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
struct platform_device {size_t id; } ;
struct bfin_twi_iface {int /*<<< orphan*/  regs_base; int /*<<< orphan*/  irq; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bfin_twi_iface*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bfin_twi_iface*) ; 
 int /*<<< orphan*/  peripheral_free_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pin_req ; 
 struct bfin_twi_iface* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i2c_bfin_twi_remove(struct platform_device *pdev)
{
	struct bfin_twi_iface *iface = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, NULL);

	i2c_del_adapter(&(iface->adap));
	free_irq(iface->irq, iface);
	peripheral_free_list(pin_req[pdev->id]);
	iounmap(iface->regs_base);
	kfree(iface);

	return 0;
}