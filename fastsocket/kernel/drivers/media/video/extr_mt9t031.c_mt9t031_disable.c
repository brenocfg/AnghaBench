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
 int /*<<< orphan*/  MT9T031_OUTPUT_CONTROL ; 
 int /*<<< orphan*/  reg_clear (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt9t031_disable(struct i2c_client *client)
{
	/* Disable the chip */
	reg_clear(client, MT9T031_OUTPUT_CONTROL, 2);

	return 0;
}