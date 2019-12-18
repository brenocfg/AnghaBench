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
struct urb {int actual_length; int status; } ;
struct timer_list {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 int /*<<< orphan*/  cxacru_timeout_kill ; 
 int /*<<< orphan*/  del_timer_sync (struct timer_list*) ; 
 int /*<<< orphan*/  init_timer (struct timer_list*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (struct completion*) ; 

__attribute__((used)) static int cxacru_start_wait_urb(struct urb *urb, struct completion *done,
				 int* actual_length)
{
	struct timer_list timer;

	init_timer(&timer);
	timer.expires = jiffies + msecs_to_jiffies(CMD_TIMEOUT);
	timer.data = (unsigned long) urb;
	timer.function = cxacru_timeout_kill;
	add_timer(&timer);
	wait_for_completion(done);
	del_timer_sync(&timer);

	if (actual_length)
		*actual_length = urb->actual_length;
	return urb->status; /* must read status after completion */
}