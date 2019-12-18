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
struct s3c2410_spigpio_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_GPH (int) ; 
 int /*<<< orphan*/  s3c2410_gpio_setpin (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void jive_wm8750_chipselect(struct s3c2410_spigpio_info *spi, int cs)
{
	s3c2410_gpio_setpin(S3C2410_GPH(10), cs ? 0 : 1);
}