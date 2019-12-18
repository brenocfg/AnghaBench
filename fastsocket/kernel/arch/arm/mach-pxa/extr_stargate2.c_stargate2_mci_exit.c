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

/* Variables and functions */
 int /*<<< orphan*/  IRQ_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SG2_GPIO_nSD_DETECT ; 
 int /*<<< orphan*/  SG2_SD_POWER_ENABLE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stargate2_mci_exit(struct device *dev, void *data)
{
	free_irq(IRQ_GPIO(SG2_GPIO_nSD_DETECT), data);
	gpio_free(SG2_SD_POWER_ENABLE);
	gpio_free(SG2_GPIO_nSD_DETECT);
}