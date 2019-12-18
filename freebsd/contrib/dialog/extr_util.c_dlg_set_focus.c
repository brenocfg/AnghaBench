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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  doupdate () ; 
 scalar_t__ getcurx (int /*<<< orphan*/ *) ; 
 scalar_t__ getcury (int /*<<< orphan*/ *) ; 
 scalar_t__ getparx (int /*<<< orphan*/ *) ; 
 scalar_t__ getpary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ *) ; 

void
dlg_set_focus(WINDOW *parent, WINDOW *win)
{
    if (win != 0) {
	(void) wmove(parent,
		     getpary(win) + getcury(win),
		     getparx(win) + getcurx(win));
	(void) wnoutrefresh(win);
	(void) doupdate();
    }
}