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
struct snd_ice1712 {struct aureon_spec* spec; } ;
struct aureon_spec {unsigned short* stac9744; } ;

/* Variables and functions */
 unsigned int AUREON_AC97_ADDR ; 
 unsigned int AUREON_AC97_COMMIT ; 
 unsigned int AUREON_AC97_DATA_HIGH ; 
 unsigned int AUREON_AC97_DATA_LOW ; 
 unsigned int AUREON_AC97_DATA_MASK ; 
 int snd_ice1712_gpio_read (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_write (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void aureon_ac97_write(struct snd_ice1712 *ice, unsigned short reg,
			      unsigned short val)
{
	struct aureon_spec *spec = ice->spec;
	unsigned int tmp;

	/* Send address to XILINX chip */
	tmp = (snd_ice1712_gpio_read(ice) & ~0xFF) | (reg & 0x7F);
	snd_ice1712_gpio_write(ice, tmp);
	udelay(10);
	tmp |= AUREON_AC97_ADDR;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(10);
	tmp &= ~AUREON_AC97_ADDR;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(10);

	/* Send low-order byte to XILINX chip */
	tmp &= ~AUREON_AC97_DATA_MASK;
	tmp |= val & AUREON_AC97_DATA_MASK;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(10);
	tmp |= AUREON_AC97_DATA_LOW;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(10);
	tmp &= ~AUREON_AC97_DATA_LOW;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(10);

	/* Send high-order byte to XILINX chip */
	tmp &= ~AUREON_AC97_DATA_MASK;
	tmp |= (val >> 8) & AUREON_AC97_DATA_MASK;

	snd_ice1712_gpio_write(ice, tmp);
	udelay(10);
	tmp |= AUREON_AC97_DATA_HIGH;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(10);
	tmp &= ~AUREON_AC97_DATA_HIGH;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(10);

	/* Instruct XILINX chip to parse the data to the STAC9744 chip */
	tmp |= AUREON_AC97_COMMIT;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(10);
	tmp &= ~AUREON_AC97_COMMIT;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(10);

	/* Store the data in out private buffer */
	spec->stac9744[(reg & 0x7F) >> 1] = val;
}