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
 int /*<<< orphan*/  S3C64XX_GPB (int) ; 
 int /*<<< orphan*/  S3C64XX_GPB2_I2C_SCL1 ; 
 int /*<<< orphan*/  S3C64XX_GPB3_I2C_SDA1 ; 
 int /*<<< orphan*/  S3C_GPIO_PULL_UP ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_gpio_setpull (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void s3c_i2c1_cfg_gpio(struct platform_device *dev)
{
	s3c_gpio_cfgpin(S3C64XX_GPB(2), S3C64XX_GPB2_I2C_SCL1);
	s3c_gpio_cfgpin(S3C64XX_GPB(3), S3C64XX_GPB3_I2C_SDA1);
	s3c_gpio_setpull(S3C64XX_GPB(2), S3C_GPIO_PULL_UP);
	s3c_gpio_setpull(S3C64XX_GPB(3), S3C_GPIO_PULL_UP);
}