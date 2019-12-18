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
struct netpoll {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __netpoll_cleanup (struct netpoll*) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void netpoll_cleanup(struct netpoll *np)
{
	if (!np->dev)
		return;

	rtnl_lock();
	__netpoll_cleanup(np);
	rtnl_unlock();

	dev_put(np->dev);
	np->dev = NULL;
}