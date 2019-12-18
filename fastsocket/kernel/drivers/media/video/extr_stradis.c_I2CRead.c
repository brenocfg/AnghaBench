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
struct saa7146 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2CWipe (struct saa7146*) ; 
 int SAA7146_I2C_BUSY ; 
 int SAA7146_I2C_ERR ; 
 int /*<<< orphan*/  SAA7146_I2C_STATUS ; 
 int /*<<< orphan*/  SAA7146_I2C_TRANSFER ; 
 int /*<<< orphan*/  SAA7146_MC2 ; 
 int SAA7146_MC2_UPLD_I2C ; 
 int /*<<< orphan*/  printk (char*) ; 
 int saaread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saawrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static int I2CRead(struct saa7146 *saa, unsigned char addr,
		   unsigned char subaddr, int dosub)
{
	int i;

	if (saaread(SAA7146_I2C_STATUS) & 0x3c)
		I2CWipe(saa);
	for (i = 0;
		i < 1000 && (saaread(SAA7146_I2C_STATUS) & SAA7146_I2C_BUSY);
		i++)
		schedule();
	if (i == 1000)
		I2CWipe(saa);
	if (dosub)
		saawrite(((addr & 0xfe) << 24) | (((addr | 1) & 0xff) << 8) |
			((subaddr & 0xff) << 16) | 0xed, SAA7146_I2C_TRANSFER);
	else
		saawrite(((addr & 0xfe) << 24) | (((addr | 1) & 0xff) << 16) |
			0xf1, SAA7146_I2C_TRANSFER);
	saawrite((SAA7146_MC2_UPLD_I2C << 16) |
		 SAA7146_MC2_UPLD_I2C, SAA7146_MC2);
	/* wait for i2c registers to be programmed */
	for (i = 0; i < 1000 &&
	     !(saaread(SAA7146_MC2) & SAA7146_MC2_UPLD_I2C); i++)
		schedule();
	/* wait for valid data */
	for (i = 0; i < 1000 &&
	     (saaread(SAA7146_I2C_STATUS) & SAA7146_I2C_BUSY); i++)
		schedule();
	if (saaread(SAA7146_I2C_STATUS) & SAA7146_I2C_ERR)
		return -1;
	if (i == 1000)
		printk("i2c setup read timeout\n");
	saawrite(0x41, SAA7146_I2C_TRANSFER);
	saawrite((SAA7146_MC2_UPLD_I2C << 16) |
		 SAA7146_MC2_UPLD_I2C, SAA7146_MC2);
	/* wait for i2c registers to be programmed */
	for (i = 0; i < 1000 &&
	     !(saaread(SAA7146_MC2) & SAA7146_MC2_UPLD_I2C); i++)
		schedule();
	/* wait for valid data */
	for (i = 0; i < 1000 &&
	     (saaread(SAA7146_I2C_TRANSFER) & SAA7146_I2C_BUSY); i++)
		schedule();
	if (saaread(SAA7146_I2C_TRANSFER) & SAA7146_I2C_ERR)
		return -1;
	if (i == 1000)
		printk("i2c read timeout\n");
	return ((saaread(SAA7146_I2C_TRANSFER) >> 24) & 0xff);
}