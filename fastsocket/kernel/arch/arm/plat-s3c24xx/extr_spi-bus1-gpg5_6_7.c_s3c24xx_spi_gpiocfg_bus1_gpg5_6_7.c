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
struct s3c2410_spi_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_GPG (int) ; 
 int /*<<< orphan*/  S3C2410_GPG5_SPIMISO1 ; 
 int /*<<< orphan*/  S3C2410_GPG6_SPIMOSI1 ; 
 int /*<<< orphan*/  S3C2410_GPG7_SPICLK1 ; 
 int /*<<< orphan*/  S3C2410_GPIO_INPUT ; 
 int /*<<< orphan*/  s3c2410_gpio_cfgpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_gpio_pullup (int /*<<< orphan*/ ,int) ; 

void s3c24xx_spi_gpiocfg_bus1_gpg5_6_7(struct s3c2410_spi_info *spi,
				       int enable)
{
	if (enable) {
		s3c2410_gpio_cfgpin(S3C2410_GPG(7), S3C2410_GPG7_SPICLK1);
		s3c2410_gpio_cfgpin(S3C2410_GPG(6), S3C2410_GPG6_SPIMOSI1);
		s3c2410_gpio_cfgpin(S3C2410_GPG(5), S3C2410_GPG5_SPIMISO1);
		s3c2410_gpio_pullup(S3C2410_GPG(5), 0);
		s3c2410_gpio_pullup(S3C2410_GPG(6), 0);
	} else {
		s3c2410_gpio_cfgpin(S3C2410_GPG(7), S3C2410_GPIO_INPUT);
		s3c2410_gpio_cfgpin(S3C2410_GPG(5), S3C2410_GPIO_INPUT);
		s3c2410_gpio_pullup(S3C2410_GPG(5), 1);
		s3c2410_gpio_pullup(S3C2410_GPG(6), 1);
		s3c2410_gpio_pullup(S3C2410_GPG(7), 1);
	}
}