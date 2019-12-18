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
struct net_device {int /*<<< orphan*/  trans_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void tms380tr_timeout(struct net_device *dev)
{
	/*
	 * If we get here, some higher level has decided we are broken.
	 * There should really be a "kick me" function call instead.
	 *
	 * Resetting the token ring adapter takes a long time so just
	 * fake transmission time and go on trying. Our own timeout
	 * routine is in tms380tr_timer_chk()
	 */
	dev->trans_start = jiffies;
	netif_wake_queue(dev);
}