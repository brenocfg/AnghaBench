#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timeout_fn ;
struct TYPE_6__ {scalar_t__ reset; } ;
struct TYPE_5__ {unsigned long expires; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 TYPE_4__* FDCS ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 TYPE_1__ fd_timer ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  reset_fdc () ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int fd_wait_for_completion(unsigned long delay, timeout_fn function)
{
	if (FDCS->reset) {
		reset_fdc();	/* do the reset during sleep to win time
				 * if we don't need to sleep, it's a good
				 * occasion anyways */
		return 1;
	}

	if (time_before(jiffies, delay)) {
		del_timer(&fd_timer);
		fd_timer.function = function;
		fd_timer.expires = delay;
		add_timer(&fd_timer);
		return 1;
	}
	return 0;
}