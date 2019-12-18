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
struct soc_camera_device {int dummy; } ;
struct mt9m111 {int /*<<< orphan*/  gain; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  mt9m111_get_global_gain (struct i2c_client*) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 
 int /*<<< orphan*/  to_soc_camera_control (struct soc_camera_device*) ; 

__attribute__((used)) static int mt9m111_suspend(struct soc_camera_device *icd, pm_message_t state)
{
	struct i2c_client *client = to_i2c_client(to_soc_camera_control(icd));
	struct mt9m111 *mt9m111 = to_mt9m111(client);

	mt9m111->gain = mt9m111_get_global_gain(client);

	return 0;
}