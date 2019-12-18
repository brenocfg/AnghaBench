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
 unsigned int AUREON_CS8415_CS ; 
 unsigned int AUREON_SPI_CLK ; 
 unsigned int AUREON_SPI_MOSI ; 
 unsigned int AUREON_WM_CS ; 
 unsigned int AUREON_WM_RW ; 
 unsigned char PCA9554_DEV ; 
 unsigned int snd_ice1712_gpio_read (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_mask (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_write (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void aureon_pca9554_write(struct snd_ice1712 *ice, unsigned char reg,
				 unsigned char data)
{
	unsigned int tmp;
	int i, j;
	unsigned char dev = PCA9554_DEV;  /* ID 0100000, write */
	unsigned char val = 0;

	tmp = snd_ice1712_gpio_read(ice);

	snd_ice1712_gpio_set_mask(ice, ~(AUREON_SPI_MOSI|AUREON_SPI_CLK|
					 AUREON_WM_RW|AUREON_WM_CS|
					 AUREON_CS8415_CS));
	tmp |= AUREON_WM_RW;
	tmp |= AUREON_CS8415_CS | AUREON_WM_CS; /* disable SPI devices */

	tmp &= ~AUREON_SPI_MOSI;
	tmp &= ~AUREON_SPI_CLK;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(50);

	/*
	 * send i2c stop condition and start condition
	 * to obtain sane state
	 */
	tmp |= AUREON_SPI_CLK;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(50);
	tmp |= AUREON_SPI_MOSI;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(100);
	tmp &= ~AUREON_SPI_MOSI;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(50);
	tmp &= ~AUREON_SPI_CLK;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(100);
	/*
	 * send device address, command and value,
	 * skipping ack cycles inbetween
	 */
	for (j = 0; j < 3; j++) {
		switch (j) {
		case 0:
			val = dev;
			break;
		case 1:
			val = reg;
			break;
		case 2:
			val = data;
			break;
		}
		for (i = 7; i >= 0; i--) {
			tmp &= ~AUREON_SPI_CLK;
			snd_ice1712_gpio_write(ice, tmp);
			udelay(40);
			if (val & (1 << i))
				tmp |= AUREON_SPI_MOSI;
			else
				tmp &= ~AUREON_SPI_MOSI;
			snd_ice1712_gpio_write(ice, tmp);
			udelay(40);
			tmp |= AUREON_SPI_CLK;
			snd_ice1712_gpio_write(ice, tmp);
			udelay(40);
		}
		tmp &= ~AUREON_SPI_CLK;
		snd_ice1712_gpio_write(ice, tmp);
		udelay(40);
		tmp |= AUREON_SPI_CLK;
		snd_ice1712_gpio_write(ice, tmp);
		udelay(40);
		tmp &= ~AUREON_SPI_CLK;
		snd_ice1712_gpio_write(ice, tmp);
		udelay(40);
	}
	tmp &= ~AUREON_SPI_CLK;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(40);
	tmp &= ~AUREON_SPI_MOSI;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(40);
	tmp |= AUREON_SPI_CLK;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(50);
	tmp |= AUREON_SPI_MOSI;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(100);
}