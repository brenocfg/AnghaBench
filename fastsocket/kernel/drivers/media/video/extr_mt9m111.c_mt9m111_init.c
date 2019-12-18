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
struct mt9m111 {int /*<<< orphan*/  autoexposure; int /*<<< orphan*/  context; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIGHPOWER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int mt9m111_enable (struct i2c_client*) ; 
 int mt9m111_reset (struct i2c_client*) ; 
 int mt9m111_set_autoexposure (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int mt9m111_set_context (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 

__attribute__((used)) static int mt9m111_init(struct i2c_client *client)
{
	struct mt9m111 *mt9m111 = to_mt9m111(client);
	int ret;

	mt9m111->context = HIGHPOWER;
	ret = mt9m111_enable(client);
	if (!ret)
		ret = mt9m111_reset(client);
	if (!ret)
		ret = mt9m111_set_context(client, mt9m111->context);
	if (!ret)
		ret = mt9m111_set_autoexposure(client, mt9m111->autoexposure);
	if (ret)
		dev_err(&client->dev, "mt9m111 init failed: %d\n", ret);
	return ret;
}