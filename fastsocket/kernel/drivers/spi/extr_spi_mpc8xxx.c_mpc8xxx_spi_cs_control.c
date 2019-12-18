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
typedef  size_t u16 ;
struct TYPE_2__ {struct device* parent; } ;
struct spi_device {size_t chip_select; TYPE_1__ dev; } ;
struct mpc8xxx_spi_probe_info {int* gpios; int* alow_flags; } ;
struct device {int /*<<< orphan*/  platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int,int) ; 
 struct mpc8xxx_spi_probe_info* to_of_pinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpc8xxx_spi_cs_control(struct spi_device *spi, bool on)
{
	struct device *dev = spi->dev.parent;
	struct mpc8xxx_spi_probe_info *pinfo = to_of_pinfo(dev->platform_data);
	u16 cs = spi->chip_select;
	int gpio = pinfo->gpios[cs];
	bool alow = pinfo->alow_flags[cs];

	gpio_set_value(gpio, on ^ alow);
}