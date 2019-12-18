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
struct TYPE_2__ {struct mv643xx_eth_shared_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mv643xx_eth_shared_private {scalar_t__ err_interrupt; int /*<<< orphan*/  base; int /*<<< orphan*/  smi_bus; } ;
struct mv643xx_eth_shared_platform_data {int /*<<< orphan*/ * shared_smi; } ;

/* Variables and functions */
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct mv643xx_eth_shared_private*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mv643xx_eth_shared_private*) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct mv643xx_eth_shared_private* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mv643xx_eth_shared_remove(struct platform_device *pdev)
{
	struct mv643xx_eth_shared_private *msp = platform_get_drvdata(pdev);
	struct mv643xx_eth_shared_platform_data *pd = pdev->dev.platform_data;

	if (pd == NULL || pd->shared_smi == NULL) {
		mdiobus_unregister(msp->smi_bus);
		mdiobus_free(msp->smi_bus);
	}
	if (msp->err_interrupt != NO_IRQ)
		free_irq(msp->err_interrupt, msp);
	iounmap(msp->base);
	kfree(msp);

	return 0;
}