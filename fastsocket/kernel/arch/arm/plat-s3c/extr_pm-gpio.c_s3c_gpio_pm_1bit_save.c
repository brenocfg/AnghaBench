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
struct s3c_gpio_chip {scalar_t__ base; void** pm_save; } ;

/* Variables and functions */
 scalar_t__ OFFS_CON ; 
 scalar_t__ OFFS_DAT ; 
 void* __raw_readl (scalar_t__) ; 

__attribute__((used)) static void s3c_gpio_pm_1bit_save(struct s3c_gpio_chip *chip)
{
	chip->pm_save[0] = __raw_readl(chip->base + OFFS_CON);
	chip->pm_save[1] = __raw_readl(chip->base + OFFS_DAT);
}