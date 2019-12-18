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
struct net_local {int /*<<< orphan*/  wait_for_tok_int; scalar_t__ Sleeping; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tms380tr_timer_end_wait(unsigned long data)
{
	struct net_device *dev = (struct net_device*)data;
	struct net_local *tp = netdev_priv(dev);

	if(tp->Sleeping)
	{
		tp->Sleeping = 0;
		wake_up_interruptible(&tp->wait_for_tok_int);
	}

	return;
}