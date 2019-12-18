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
struct shutdown_trigger {TYPE_1__* action; } ;
struct TYPE_2__ {int init_rc; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int SHUTDOWN_ACTIONS_COUNT ; 
 TYPE_1__** shutdown_actions_list ; 
 scalar_t__ sysfs_streq (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_trigger(const char *buf, struct shutdown_trigger *trigger,
		       size_t len)
{
	int i;

	for (i = 0; i < SHUTDOWN_ACTIONS_COUNT; i++) {
		if (sysfs_streq(buf, shutdown_actions_list[i]->name)) {
			if (shutdown_actions_list[i]->init_rc) {
				return shutdown_actions_list[i]->init_rc;
			} else {
				trigger->action = shutdown_actions_list[i];
				return len;
			}
		}
	}
	return -EINVAL;
}