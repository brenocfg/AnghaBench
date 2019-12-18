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
struct saa7146 {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int I2CRead (struct saa7146*,int,int,int) ; 
 int /*<<< orphan*/  I2CWrite (struct saa7146*,int,int,int,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static void initialize_cs4341(struct saa7146 *saa)
{
	int i;
	for (i = 0; i < 200; i++) {
		/* auto mute off, power on, no de-emphasis */
		/* I2S data up to 24-bit 64xFs internal SCLK */
		I2CWrite(saa, 0x22, 0x01, 0x11, 2);
		/* ATAPI mixer settings */
		I2CWrite(saa, 0x22, 0x02, 0x49, 2);
		/* attenuation left 3db */
		I2CWrite(saa, 0x22, 0x03, 0x00, 2);
		/* attenuation right 3db */
		I2CWrite(saa, 0x22, 0x04, 0x00, 2);
		I2CWrite(saa, 0x22, 0x01, 0x10, 2);
		if (I2CRead(saa, 0x22, 0x02, 1) == 0x49)
			break;
		schedule();
	}
	printk("stradis%d: CS4341 initialized (%d)\n", saa->nr, i);
	return;
}