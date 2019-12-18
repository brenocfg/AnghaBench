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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dn_fib_flush () ; 
 scalar_t__ dn_fib_sync_down (int /*<<< orphan*/ ,struct net_device*,int) ; 
 int /*<<< orphan*/  dn_neigh_table ; 
 int /*<<< orphan*/  dn_rt_cache_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_ifdown (int /*<<< orphan*/ *,struct net_device*) ; 

__attribute__((used)) static void dn_fib_disable_addr(struct net_device *dev, int force)
{
	if (dn_fib_sync_down(0, dev, force))
		dn_fib_flush();
	dn_rt_cache_flush(0);
	neigh_ifdown(&dn_neigh_table, dev);
}