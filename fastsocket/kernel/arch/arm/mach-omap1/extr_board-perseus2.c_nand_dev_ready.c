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
struct omap_nand_platform_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2_NAND_RB_GPIO_PIN ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nand_dev_ready(struct omap_nand_platform_data *data)
{
	return gpio_get_value(P2_NAND_RB_GPIO_PIN);
}