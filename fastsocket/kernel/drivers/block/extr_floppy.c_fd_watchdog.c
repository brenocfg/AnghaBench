#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ timeout_fn ;
struct TYPE_8__ {int flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* done ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ expires; scalar_t__ function; } ;

/* Variables and functions */
 TYPE_5__* DP ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int FD_DEBUG ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  cancel_activity () ; 
 TYPE_3__* cont ; 
 int /*<<< orphan*/  current_drive ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ disk_change (int /*<<< orphan*/ ) ; 
 TYPE_1__ fd_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  reset_fdc () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fd_watchdog(void)
{
#ifdef DCL_DEBUG
	if (DP->flags & FD_DEBUG) {
		DPRINT("calling disk change from watchdog\n");
	}
#endif

	if (disk_change(current_drive)) {
		DPRINT("disk removed during i/o\n");
		cancel_activity();
		cont->done(0);
		reset_fdc();
	} else {
		del_timer(&fd_timer);
		fd_timer.function = (timeout_fn) fd_watchdog;
		fd_timer.expires = jiffies + HZ / 10;
		add_timer(&fd_timer);
	}
}