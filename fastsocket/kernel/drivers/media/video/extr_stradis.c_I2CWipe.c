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
 int SAA7146_I2C_ABORT ; 
 int /*<<< orphan*/  SAA7146_I2C_STATUS ; 
 int /*<<< orphan*/  SAA7146_MC2 ; 
 int SAA7146_MC2_UPLD_I2C ; 
 int saaread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saawrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static void I2CWipe(struct saa7146 *saa)
{
	int i;
	/* set i2c to ~=100kHz, abort transfer, clear busy */
	saawrite(0x600 | SAA7146_I2C_ABORT, SAA7146_I2C_STATUS);
	saawrite((SAA7146_MC2_UPLD_I2C << 16) |
		 SAA7146_MC2_UPLD_I2C, SAA7146_MC2);
	/* wait for i2c registers to be programmed */
	for (i = 0; i < 1000 &&
	     !(saaread(SAA7146_MC2) & SAA7146_MC2_UPLD_I2C); i++)
		schedule();
	saawrite(0x600, SAA7146_I2C_STATUS);
	saawrite((SAA7146_MC2_UPLD_I2C << 16) |
		 SAA7146_MC2_UPLD_I2C, SAA7146_MC2);
	/* wait for i2c registers to be programmed */
	for (i = 0; i < 1000 &&
	     !(saaread(SAA7146_MC2) & SAA7146_MC2_UPLD_I2C); i++)
		schedule();
	saawrite(0x600, SAA7146_I2C_STATUS);
	saawrite((SAA7146_MC2_UPLD_I2C << 16) |
		 SAA7146_MC2_UPLD_I2C, SAA7146_MC2);
	/* wait for i2c registers to be programmed */
	for (i = 0; i < 1000 &&
	     !(saaread(SAA7146_MC2) & SAA7146_MC2_UPLD_I2C); i++)
		schedule();
}