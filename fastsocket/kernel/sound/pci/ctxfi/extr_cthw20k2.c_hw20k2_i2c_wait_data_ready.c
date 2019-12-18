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
struct hw {int dummy; } ;

/* Variables and functions */
 unsigned int DATA_READY ; 
 int /*<<< orphan*/  I2C_IF_STATUS ; 
 unsigned int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw20k2_i2c_wait_data_ready(struct hw *hw)
{
	int i = 0x400000;
	unsigned int ret;

	do {
		ret = hw_read_20kx(hw, I2C_IF_STATUS);
	} while ((!(ret & DATA_READY)) && --i);

	return i;
}