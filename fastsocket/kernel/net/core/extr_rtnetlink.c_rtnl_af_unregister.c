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
struct rtnl_af_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rtnl_af_unregister (struct rtnl_af_ops*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void rtnl_af_unregister(struct rtnl_af_ops *ops)
{
	rtnl_lock();
	__rtnl_af_unregister(ops);
	rtnl_unlock();
}