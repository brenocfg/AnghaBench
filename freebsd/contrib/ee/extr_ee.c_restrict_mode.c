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

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int clear_com_win ; 
 int /*<<< orphan*/  com_win ; 
 int /*<<< orphan*/  restricted ; 
 int /*<<< orphan*/  restricted_msg ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

int
restrict_mode()
{
	if (!restricted)
		return(FALSE);

	wmove(com_win, 0, 0);
	wprintw(com_win, restricted_msg);
	wclrtoeol(com_win);
	wrefresh(com_win);
	clear_com_win = TRUE;
	return(TRUE);
}