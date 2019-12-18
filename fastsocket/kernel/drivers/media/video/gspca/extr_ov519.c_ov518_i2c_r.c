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
typedef  int u8 ;
struct sd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBI ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  R518_I2C_CTL ; 
 int /*<<< orphan*/  R51x_I2C_DATA ; 
 int /*<<< orphan*/  R51x_I2C_SADDR_2 ; 
 int reg_r (struct sd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov518_i2c_r(struct sd *sd, u8 reg)
{
	int value;

	/* Select camera register */
	reg_w(sd, R51x_I2C_SADDR_2, reg);

	/* Initiate 2-byte write cycle */
	reg_w(sd, R518_I2C_CTL, 0x03);

	/* Initiate 2-byte read cycle */
	reg_w(sd, R518_I2C_CTL, 0x05);
	value = reg_r(sd, R51x_I2C_DATA);
	PDEBUG(D_USBI, "ov518_i2c_r %02x %02x", reg, value);
	return value;
}