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
struct cx25821_dev {int /*<<< orphan*/ * i2c_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx25821_i2c_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

void cx_i2c_read_print(struct cx25821_dev *dev, u32 reg, const char *reg_string)
{
	int tmp = 0;
	u32 value = 0;

	value = cx25821_i2c_read(&dev->i2c_bus[0], reg, &tmp);
}