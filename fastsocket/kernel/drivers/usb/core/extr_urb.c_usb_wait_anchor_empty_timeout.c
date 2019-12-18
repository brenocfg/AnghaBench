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
struct usb_anchor {int /*<<< orphan*/  urb_list; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int usb_wait_anchor_empty_timeout(struct usb_anchor *anchor,
				  unsigned int timeout)
{
	return wait_event_timeout(anchor->wait, list_empty(&anchor->urb_list),
				  msecs_to_jiffies(timeout));
}