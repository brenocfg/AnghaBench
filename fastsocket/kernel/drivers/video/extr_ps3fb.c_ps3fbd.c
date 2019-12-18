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
struct fb_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ is_kicked; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  acquire_console_sem () ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 TYPE_1__ ps3fb ; 
 int /*<<< orphan*/  ps3fb_sync (struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_console_sem () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  try_to_freeze () ; 

__attribute__((used)) static int ps3fbd(void *arg)
{
	struct fb_info *info = arg;

	set_freezable();
	while (!kthread_should_stop()) {
		try_to_freeze();
		set_current_state(TASK_INTERRUPTIBLE);
		if (ps3fb.is_kicked) {
			ps3fb.is_kicked = 0;
			acquire_console_sem();
			ps3fb_sync(info, 0);	/* single buffer */
			release_console_sem();
		}
		schedule();
	}
	return 0;
}