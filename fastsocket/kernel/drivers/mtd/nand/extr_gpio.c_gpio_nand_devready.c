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
struct mtd_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio_rdy; } ;
struct gpiomtd {TYPE_1__ plat; } ;

/* Variables and functions */
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 struct gpiomtd* gpio_nand_getpriv (struct mtd_info*) ; 

__attribute__((used)) static int gpio_nand_devready(struct mtd_info *mtd)
{
	struct gpiomtd *gpiomtd = gpio_nand_getpriv(mtd);
	return gpio_get_value(gpiomtd->plat.gpio_rdy);
}