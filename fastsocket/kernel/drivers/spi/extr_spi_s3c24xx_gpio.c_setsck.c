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
struct spi_device {int dummy; } ;
struct s3c2410_spigpio {TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  s3c2410_gpio_setpin (int /*<<< orphan*/ ,int) ; 
 struct s3c2410_spigpio* spidev_to_sg (struct spi_device*) ; 

__attribute__((used)) static inline void setsck(struct spi_device *dev, int on)
{
	struct s3c2410_spigpio *sg = spidev_to_sg(dev);
	s3c2410_gpio_setpin(sg->info->pin_clk, on ? 1 : 0);
}