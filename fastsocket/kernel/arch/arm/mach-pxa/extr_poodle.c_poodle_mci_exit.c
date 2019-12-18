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
 int /*<<< orphan*/  POODLE_GPIO_SD_PWR ; 
 int /*<<< orphan*/  POODLE_GPIO_SD_PWR1 ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poodle_mci_exit(struct device *dev, void *data)
{
	gpio_free(POODLE_GPIO_SD_PWR1);
	gpio_free(POODLE_GPIO_SD_PWR);
}