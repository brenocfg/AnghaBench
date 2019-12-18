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
 scalar_t__ COLS ; 
 scalar_t__ LINES ; 
 int /*<<< orphan*/  com_win ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  help_win ; 
 int /*<<< orphan*/  info_win ; 
 scalar_t__ info_window ; 
 scalar_t__ local_COLS ; 
 scalar_t__ local_LINES ; 
 int /*<<< orphan*/  redraw () ; 
 int /*<<< orphan*/  set_up_term () ; 
 int /*<<< orphan*/  text_win ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

void 
resize_check()
{
	if ((LINES == local_LINES) && (COLS == local_COLS))
		return;

	if (info_window)
		delwin(info_win);
	delwin(text_win);
	delwin(com_win);
	delwin(help_win);
	set_up_term();
	redraw();
	wrefresh(text_win);
}