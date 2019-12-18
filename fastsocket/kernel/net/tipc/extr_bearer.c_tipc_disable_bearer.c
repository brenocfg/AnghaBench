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
 int bearer_disable (char const*) ; 
 int /*<<< orphan*/  tipc_net_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int tipc_disable_bearer(const char *name)
{
	int res;

	write_lock_bh(&tipc_net_lock);
	res = bearer_disable(name);
	write_unlock_bh(&tipc_net_lock);
	return res;
}