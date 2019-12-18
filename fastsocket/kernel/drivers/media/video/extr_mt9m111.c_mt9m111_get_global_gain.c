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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_GAIN ; 
 int reg_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9m111_get_global_gain(struct i2c_client *client)
{
	int data;

	data = reg_read(GLOBAL_GAIN);
	if (data >= 0)
		return (data & 0x2f) * (1 << ((data >> 10) & 1)) *
			(1 << ((data >> 9) & 1));
	return data;
}