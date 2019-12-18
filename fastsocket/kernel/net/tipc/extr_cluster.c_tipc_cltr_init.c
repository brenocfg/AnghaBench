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
 int ENOMEM ; 
 scalar_t__ LOWEST_SLAVE ; 
 scalar_t__ tipc_cltr_create (int /*<<< orphan*/ ) ; 
 scalar_t__ tipc_highest_allowed_slave ; 
 scalar_t__ tipc_max_slaves ; 
 int /*<<< orphan*/  tipc_own_addr ; 

int tipc_cltr_init(void)
{
	tipc_highest_allowed_slave = LOWEST_SLAVE + tipc_max_slaves;
	return tipc_cltr_create(tipc_own_addr) ? 0 : -ENOMEM;
}