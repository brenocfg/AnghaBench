#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;
struct tas {int /*<<< orphan*/  mtx; TYPE_1__ codec; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAS_ACR_ANALOG_PDOWN ; 
 int /*<<< orphan*/  TAS_REG_ACR ; 
 int /*<<< orphan*/  aoa_codec_unregister (TYPE_1__*) ; 
 struct tas* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct tas*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tas_write_reg (struct tas*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tas_i2c_remove(struct i2c_client *client)
{
	struct tas *tas = i2c_get_clientdata(client);
	u8 tmp = TAS_ACR_ANALOG_PDOWN;

	aoa_codec_unregister(&tas->codec);
	of_node_put(tas->codec.node);

	/* power down codec chip */
	tas_write_reg(tas, TAS_REG_ACR, 1, &tmp);

	mutex_destroy(&tas->mtx);
	kfree(tas);
	return 0;
}