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
struct platform_device {int dummy; } ;

/* Variables and functions */
 unsigned int S3C64XX_GPG (int) ; 
 int /*<<< orphan*/  S3C_GPIO_PULL_NONE ; 
 int /*<<< orphan*/  S3C_GPIO_PULL_UP ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_gpio_setpull (unsigned int,int /*<<< orphan*/ ) ; 

void s3c64xx_setup_sdhci0_cfg_gpio(struct platform_device *dev, int width)
{
	unsigned int gpio;
	unsigned int end;

	end = S3C64XX_GPG(2 + width);

	/* Set all the necessary GPG pins to special-function 0 */
	for (gpio = S3C64XX_GPG(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	s3c_gpio_setpull(S3C64XX_GPG(6), S3C_GPIO_PULL_UP);
	s3c_gpio_cfgpin(S3C64XX_GPG(6), S3C_GPIO_SFN(2));
}