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
struct mt9m111 {int autowhitebalance; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9M111_OPMODE_AUTOWHITEBAL_EN ; 
 int /*<<< orphan*/  OPER_MODE_CTRL ; 
 int reg_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 

__attribute__((used)) static int mt9m111_set_autowhitebalance(struct i2c_client *client, int on)
{
	struct mt9m111 *mt9m111 = to_mt9m111(client);
	int ret;

	if (on)
		ret = reg_set(OPER_MODE_CTRL, MT9M111_OPMODE_AUTOWHITEBAL_EN);
	else
		ret = reg_clear(OPER_MODE_CTRL, MT9M111_OPMODE_AUTOWHITEBAL_EN);

	if (!ret)
		mt9m111->autowhitebalance = on;

	return ret;
}