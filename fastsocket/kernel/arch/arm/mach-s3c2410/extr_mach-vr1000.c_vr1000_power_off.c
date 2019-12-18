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

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_GPB (int) ; 
 int /*<<< orphan*/  S3C2410_GPIO_OUTPUT ; 
 int /*<<< orphan*/  s3c2410_gpio_cfgpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_gpio_setpin (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vr1000_power_off(void)
{
	s3c2410_gpio_cfgpin(S3C2410_GPB(9), S3C2410_GPIO_OUTPUT);
	s3c2410_gpio_setpin(S3C2410_GPB(9), 1);
}