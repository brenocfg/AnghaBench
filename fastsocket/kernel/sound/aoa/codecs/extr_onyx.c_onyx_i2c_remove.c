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
struct TYPE_2__ {int /*<<< orphan*/  node; } ;
struct onyx {struct onyx* codec_info; TYPE_1__ codec; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aoa_codec_unregister (TYPE_1__*) ; 
 struct onyx* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct onyx*) ; 
 int /*<<< orphan*/  kfree (struct onyx*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int onyx_i2c_remove(struct i2c_client *client)
{
	struct onyx *onyx = i2c_get_clientdata(client);

	aoa_codec_unregister(&onyx->codec);
	of_node_put(onyx->codec.node);
	if (onyx->codec_info)
		kfree(onyx->codec_info);
	i2c_set_clientdata(client, onyx);
	kfree(onyx);
	return 0;
}