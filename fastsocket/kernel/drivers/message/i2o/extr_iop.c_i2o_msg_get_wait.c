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
struct i2o_message {int dummy; } ;
struct i2o_controller {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct i2o_message* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct i2o_message*) ; 
 struct i2o_message* i2o_msg_get (struct i2o_controller*) ; 
 int jiffies ; 
 int /*<<< orphan*/  osm_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_after (int,unsigned long) ; 

struct i2o_message *i2o_msg_get_wait(struct i2o_controller *c, int wait)
{
	unsigned long timeout = jiffies + wait * HZ;
	struct i2o_message *msg;

	while (IS_ERR(msg = i2o_msg_get(c))) {
		if (time_after(jiffies, timeout)) {
			osm_debug("%s: Timeout waiting for message frame.\n",
				  c->name);
			return ERR_PTR(-ETIMEDOUT);
		}
		schedule_timeout_uninterruptible(1);
	}

	return msg;
}