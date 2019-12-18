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
struct TYPE_2__ {int write_mask; int direction; } ;
struct snd_ice1712 {TYPE_1__ gpio; } ;

/* Variables and functions */
 int PONTIS_CS_CLK ; 
 int PONTIS_CS_CS ; 
 int PONTIS_CS_WDATA ; 
 int /*<<< orphan*/  set_gpio_bit (struct snd_ice1712*,int,int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_dir (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_mask (struct snd_ice1712*,int) ; 
 unsigned int spi_read_byte (struct snd_ice1712*) ; 
 int /*<<< orphan*/  spi_send_byte (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int spi_read(struct snd_ice1712 *ice, unsigned int dev, unsigned int reg)
{
	unsigned int val;
	snd_ice1712_gpio_set_dir(ice, PONTIS_CS_CS|PONTIS_CS_WDATA|PONTIS_CS_CLK);
	snd_ice1712_gpio_set_mask(ice, ~(PONTIS_CS_CS|PONTIS_CS_WDATA|PONTIS_CS_CLK));
	set_gpio_bit(ice, PONTIS_CS_CS, 0);
	spi_send_byte(ice, dev & ~1); /* WRITE */
	spi_send_byte(ice, reg); /* MAP */
	/* trigger */
	set_gpio_bit(ice, PONTIS_CS_CS, 1);
	udelay(1);
	set_gpio_bit(ice, PONTIS_CS_CS, 0);
	spi_send_byte(ice, dev | 1); /* READ */
	val = spi_read_byte(ice);
	/* trigger */
	set_gpio_bit(ice, PONTIS_CS_CS, 1);
	udelay(1);
	/* restore */
	snd_ice1712_gpio_set_mask(ice, ice->gpio.write_mask);
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
	return val;
}