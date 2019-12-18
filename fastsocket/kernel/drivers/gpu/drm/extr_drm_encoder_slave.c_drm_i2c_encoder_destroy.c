#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct i2c_client {TYPE_2__* driver; } ;
struct drm_encoder_slave {int /*<<< orphan*/ * bus_priv; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_3__ {struct module* owner; } ;
struct TYPE_4__ {TYPE_1__ driver; } ;

/* Variables and functions */
 struct i2c_client* drm_i2c_encoder_get_client (struct drm_encoder*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 struct drm_encoder_slave* to_encoder_slave (struct drm_encoder*) ; 

void drm_i2c_encoder_destroy(struct drm_encoder *drm_encoder)
{
	struct drm_encoder_slave *encoder = to_encoder_slave(drm_encoder);
	struct i2c_client *client = drm_i2c_encoder_get_client(drm_encoder);
	struct module *module = client->driver->driver.owner;

	i2c_unregister_device(client);
	encoder->bus_priv = NULL;

	module_put(module);
}