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
typedef  unsigned int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 unsigned int i2c_av_read (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_av_write (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void i2c_av_and_or(struct i2c_adapter *i2c, u16 reg, unsigned and_mask,
								u8 or_value)
{
	i2c_av_write(i2c, reg, (i2c_av_read(i2c, reg) & and_mask) | or_value);
}