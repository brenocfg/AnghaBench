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
struct nfnetlink_subsystem {size_t subsys_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfnl_lock () ; 
 int /*<<< orphan*/  nfnl_unlock () ; 
 int /*<<< orphan*/ ** subsys_table ; 

int nfnetlink_subsys_unregister(const struct nfnetlink_subsystem *n)
{
	nfnl_lock();
	subsys_table[n->subsys_id] = NULL;
	nfnl_unlock();

	return 0;
}