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
 unsigned int S3C64XX_GPI (int) ; 
 unsigned int S3C64XX_GPJ (int) ; 
 int /*<<< orphan*/  S3C_GPIO_PULL_NONE ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_gpio_setpull (unsigned int,int /*<<< orphan*/ ) ; 

extern void s3c64xx_fb_gpio_setup_24bpp(void)
{
	unsigned int gpio;

	for (gpio = S3C64XX_GPI(0); gpio <= S3C64XX_GPI(15); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	for (gpio = S3C64XX_GPJ(0); gpio <= S3C64XX_GPJ(11); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}
}