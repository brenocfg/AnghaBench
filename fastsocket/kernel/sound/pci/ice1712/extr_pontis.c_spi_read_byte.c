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
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PONTIS_CS_CLK ; 
 int PONTIS_CS_RDATA ; 
 int /*<<< orphan*/  set_gpio_bit (struct snd_ice1712*,int /*<<< orphan*/ ,int) ; 
 int snd_ice1712_gpio_read (struct snd_ice1712*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int spi_read_byte(struct snd_ice1712 *ice)
{
	int i;
	unsigned int val = 0;

	for (i = 0; i < 8; i++) {
		val <<= 1;
		set_gpio_bit(ice, PONTIS_CS_CLK, 0);
		udelay(1);
		if (snd_ice1712_gpio_read(ice) & PONTIS_CS_RDATA)
			val |= 1;
		udelay(1);
		set_gpio_bit(ice, PONTIS_CS_CLK, 1);
		udelay(1);
	}
	return val;
}