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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int RTNL_FAMILY_MAX ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** rtnl_msg_handlers ; 

void rtnl_unregister_all(int protocol)
{
	BUG_ON(protocol < 0 || protocol > RTNL_FAMILY_MAX);

	kfree(rtnl_msg_handlers[protocol]);
	rtnl_msg_handlers[protocol] = NULL;
}