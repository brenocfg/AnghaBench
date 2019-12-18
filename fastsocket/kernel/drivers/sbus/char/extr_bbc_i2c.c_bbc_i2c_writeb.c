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
struct bbc_i2c_client {int address; unsigned char bus; struct bbc_i2c_bus* bp; } ;
struct bbc_i2c_bus {int /*<<< orphan*/ * i2c_control_regs; int /*<<< orphan*/ * i2c_bussel_reg; } ;

/* Variables and functions */
 int I2C_PCF_LRB ; 
 unsigned char I2C_PCF_START ; 
 unsigned char I2C_PCF_STOP ; 
 scalar_t__ wait_for_pin (struct bbc_i2c_bus*,int*) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

int bbc_i2c_writeb(struct bbc_i2c_client *client, unsigned char val, int off)
{
	struct bbc_i2c_bus *bp = client->bp;
	int address = client->address;
	u8 status;
	int ret = -1;

	if (bp->i2c_bussel_reg != NULL)
		writeb(client->bus, bp->i2c_bussel_reg);

	writeb(address, bp->i2c_control_regs + 0x1);
	writeb(I2C_PCF_START, bp->i2c_control_regs + 0x0);
	if (wait_for_pin(bp, &status))
		goto out;

	writeb(off, bp->i2c_control_regs + 0x1);
	if (wait_for_pin(bp, &status) ||
	    (status & I2C_PCF_LRB) != 0)
		goto out;

	writeb(val, bp->i2c_control_regs + 0x1);
	if (wait_for_pin(bp, &status))
		goto out;

	ret = 0;

out:
	writeb(I2C_PCF_STOP, bp->i2c_control_regs + 0x0);
	return ret;
}