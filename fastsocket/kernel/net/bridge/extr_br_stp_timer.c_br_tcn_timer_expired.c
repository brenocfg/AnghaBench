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
struct net_bridge {int /*<<< orphan*/  lock; scalar_t__ bridge_hello_time; int /*<<< orphan*/  tcn_timer; TYPE_1__* dev; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  br_transmit_tcn (struct net_bridge*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_tcn_timer_expired(unsigned long arg)
{
	struct net_bridge *br = (struct net_bridge *) arg;

	pr_debug("%s: tcn timer expired\n", br->dev->name);
	spin_lock(&br->lock);
	if (br->dev->flags & IFF_UP) {
		br_transmit_tcn(br);

		mod_timer(&br->tcn_timer,jiffies + br->bridge_hello_time);
	}
	spin_unlock(&br->lock);
}