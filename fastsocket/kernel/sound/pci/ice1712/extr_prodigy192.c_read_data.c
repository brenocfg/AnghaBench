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
 unsigned int VT1724_PRODIGY192_CCLK ; 
 int VT1724_PRODIGY192_CDIN ; 
 int snd_ice1712_gpio_read (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_write (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned char read_data(struct snd_ice1712 *ice, unsigned int gpio,
			       int idx)
{
	unsigned char data = 0;

	for (; idx >= 0; idx--) {
		/* drop clock */
		gpio &= ~VT1724_PRODIGY192_CCLK;
		snd_ice1712_gpio_write(ice, gpio);
		udelay(1);
		/* read data */
		if (snd_ice1712_gpio_read(ice) & VT1724_PRODIGY192_CDIN)
			data |= (1 << idx);
		udelay(1);
		/* raise clock */
		gpio |= VT1724_PRODIGY192_CCLK;
		snd_ice1712_gpio_write(ice, gpio);
		udelay(1);
	}
	return data;
}