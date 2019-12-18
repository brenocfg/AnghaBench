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
 int EIO ; 
 int /*<<< orphan*/  MT9T031_OUTPUT_CONTROL ; 
 int /*<<< orphan*/  MT9T031_RESET ; 
 int reg_clear (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt9t031_idle(struct i2c_client *client)
{
	int ret;

	/* Disable chip output, synchronous option update */
	ret = reg_write(client, MT9T031_RESET, 1);
	if (ret >= 0)
		ret = reg_write(client, MT9T031_RESET, 0);
	if (ret >= 0)
		ret = reg_clear(client, MT9T031_OUTPUT_CONTROL, 2);

	return ret >= 0 ? 0 : -EIO;
}