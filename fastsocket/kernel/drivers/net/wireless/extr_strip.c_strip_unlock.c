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
struct TYPE_2__ {scalar_t__ expires; } ;
struct strip {int /*<<< orphan*/  dev; TYPE_1__ idle_timer; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void strip_unlock(struct strip *strip_info)
{
	/*
	 * Set the timer to go off in one second.
	 */
	strip_info->idle_timer.expires = jiffies + 1 * HZ;
	add_timer(&strip_info->idle_timer);
	netif_wake_queue(strip_info->dev);
}