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
struct i2c_msg {int addr; int flags; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int I2C_M_REV_DIR_ADDR ; 

__attribute__((used)) static inline unsigned char 
iic_cook_addr(struct i2c_msg *msg) 
{
	unsigned char addr;

	addr = (msg->addr << 1);

	if (msg->flags & I2C_M_RD)
		addr |= 1;

	/*
	 * Read or Write?
	 */
	if (msg->flags & I2C_M_REV_DIR_ADDR)
		addr ^= 1;

	return addr;   
}