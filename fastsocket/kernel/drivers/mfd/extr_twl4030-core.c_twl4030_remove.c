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
struct twl4030_client {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 unsigned int TWL4030_NUM_SLAVES ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int inuse ; 
 struct twl4030_client* twl4030_modules ; 
 int twl_exit_irq () ; 

__attribute__((used)) static int twl4030_remove(struct i2c_client *client)
{
	unsigned i;
	int status;

	status = twl_exit_irq();
	if (status < 0)
		return status;

	for (i = 0; i < TWL4030_NUM_SLAVES; i++) {
		struct twl4030_client	*twl = &twl4030_modules[i];

		if (twl->client && twl->client != client)
			i2c_unregister_device(twl->client);
		twl4030_modules[i].client = NULL;
	}
	inuse = false;
	return 0;
}