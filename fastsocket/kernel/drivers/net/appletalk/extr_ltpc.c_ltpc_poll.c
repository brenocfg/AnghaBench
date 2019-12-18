#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ expires; } ;

/* Variables and functions */
 int DEBUG_VERBOSE ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int debug ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  idle (struct net_device*) ; 
 scalar_t__ jiffies ; 
 int ltpc_poll_counter ; 
 TYPE_1__ ltpc_timer ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void ltpc_poll(unsigned long l)
{
	struct net_device *dev = (struct net_device *) l;

	del_timer(&ltpc_timer);

	if(debug & DEBUG_VERBOSE) {
		if (!ltpc_poll_counter) {
			ltpc_poll_counter = 50;
			printk("ltpc poll is alive\n");
		}
		ltpc_poll_counter--;
	}
  
	if (!dev)
		return;  /* we've been downed */

	/* poll 20 times per second */
	idle(dev);
	ltpc_timer.expires = jiffies + HZ/20;
	
	add_timer(&ltpc_timer);
}