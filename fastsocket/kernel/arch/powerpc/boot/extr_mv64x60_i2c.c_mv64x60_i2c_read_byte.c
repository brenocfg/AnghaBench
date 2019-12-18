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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ MV64x60_I2C_REG_CONTROL ; 
 scalar_t__ MV64x60_I2C_REG_DATA ; 
 scalar_t__ ctlr_base ; 
 int in_le32 (int /*<<< orphan*/ *) ; 
 scalar_t__ mv64x60_i2c_wait_for_status (int) ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mv64x60_i2c_read_byte(int control, int status)
{
	out_le32((u32 *)(ctlr_base + MV64x60_I2C_REG_CONTROL), control & 0xff);
	if (mv64x60_i2c_wait_for_status(status) < 0)
		return -1;
	return in_le32((u32 *)(ctlr_base + MV64x60_I2C_REG_DATA)) & 0xff;
}