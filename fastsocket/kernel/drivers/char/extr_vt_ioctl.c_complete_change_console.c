#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mode; int /*<<< orphan*/  acqsig; } ;
struct vc_data {unsigned char vc_mode; int /*<<< orphan*/  vc_num; TYPE_1__ vt_mode; int /*<<< orphan*/  vt_pid; } ;
struct TYPE_6__ {TYPE_2__* d; } ;
struct TYPE_5__ {unsigned char vc_mode; } ;

/* Variables and functions */
 unsigned char KD_TEXT ; 
 int /*<<< orphan*/  VT_EVENT_SWITCH ; 
 scalar_t__ VT_PROCESS ; 
 int /*<<< orphan*/  do_blank_screen (int) ; 
 int /*<<< orphan*/  do_unblank_screen (int) ; 
 size_t fg_console ; 
 scalar_t__ kill_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t last_console ; 
 int /*<<< orphan*/  reset_vc (struct vc_data*) ; 
 int /*<<< orphan*/  switch_screen (struct vc_data*) ; 
 TYPE_3__* vc_cons ; 
 int /*<<< orphan*/  vt_event_post (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void complete_change_console(struct vc_data *vc)
{
	unsigned char old_vc_mode;
	int old = fg_console;

	last_console = fg_console;

	/*
	 * If we're switching, we could be going from KD_GRAPHICS to
	 * KD_TEXT mode or vice versa, which means we need to blank or
	 * unblank the screen later.
	 */
	old_vc_mode = vc_cons[fg_console].d->vc_mode;
	switch_screen(vc);

	/*
	 * This can't appear below a successful kill_pid().  If it did,
	 * then the *blank_screen operation could occur while X, having
	 * received acqsig, is waking up on another processor.  This
	 * condition can lead to overlapping accesses to the VGA range
	 * and the framebuffer (causing system lockups).
	 *
	 * To account for this we duplicate this code below only if the
	 * controlling process is gone and we've called reset_vc.
	 */
	if (old_vc_mode != vc->vc_mode) {
		if (vc->vc_mode == KD_TEXT)
			do_unblank_screen(1);
		else
			do_blank_screen(1);
	}

	/*
	 * If this new console is under process control, send it a signal
	 * telling it that it has acquired. Also check if it has died and
	 * clean up (similar to logic employed in change_console())
	 */
	if (vc->vt_mode.mode == VT_PROCESS) {
		/*
		 * Send the signal as privileged - kill_pid() will
		 * tell us if the process has gone or something else
		 * is awry
		 */
		if (kill_pid(vc->vt_pid, vc->vt_mode.acqsig, 1) != 0) {
		/*
		 * The controlling process has died, so we revert back to
		 * normal operation. In this case, we'll also change back
		 * to KD_TEXT mode. I'm not sure if this is strictly correct
		 * but it saves the agony when the X server dies and the screen
		 * remains blanked due to KD_GRAPHICS! It would be nice to do
		 * this outside of VT_PROCESS but there is no single process
		 * to account for and tracking tty count may be undesirable.
		 */
			reset_vc(vc);

			if (old_vc_mode != vc->vc_mode) {
				if (vc->vc_mode == KD_TEXT)
					do_unblank_screen(1);
				else
					do_blank_screen(1);
			}
		}
	}

	/*
	 * Wake anyone waiting for their VT to activate
	 */
	vt_event_post(VT_EVENT_SWITCH, old, vc->vc_num);
	return;
}