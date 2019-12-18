#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ callback; } ;

/* Variables and functions */
 int MAX_USERID ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  reg_callback (TYPE_1__*) ; 
 TYPE_1__* users ; 

void tipc_reg_stop(void)
{
	int id;

	if (!users)
		return;

	for (id = 1; id <= MAX_USERID; id++) {
		if (users[id].callback)
			reg_callback(&users[id]);
	}
	kfree(users);
	users = NULL;
}