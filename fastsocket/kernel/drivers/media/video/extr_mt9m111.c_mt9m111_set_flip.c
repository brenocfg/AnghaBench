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
struct mt9m111 {scalar_t__ context; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ HIGHPOWER ; 
 int /*<<< orphan*/  READ_MODE_A ; 
 int /*<<< orphan*/  READ_MODE_B ; 
 int reg_clear (int /*<<< orphan*/ ,int) ; 
 int reg_set (int /*<<< orphan*/ ,int) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 

__attribute__((used)) static int mt9m111_set_flip(struct i2c_client *client, int flip, int mask)
{
	struct mt9m111 *mt9m111 = to_mt9m111(client);
	int ret;

	if (mt9m111->context == HIGHPOWER) {
		if (flip)
			ret = reg_set(READ_MODE_B, mask);
		else
			ret = reg_clear(READ_MODE_B, mask);
	} else {
		if (flip)
			ret = reg_set(READ_MODE_A, mask);
		else
			ret = reg_clear(READ_MODE_A, mask);
	}

	return ret;
}