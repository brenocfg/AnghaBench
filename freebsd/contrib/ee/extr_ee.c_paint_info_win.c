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
 scalar_t__ COMMANDS ; 
 scalar_t__ CONTROL_KEYS ; 
 int /*<<< orphan*/ * command_strings ; 
 int /*<<< orphan*/ * control_keys ; 
 int /*<<< orphan*/ * emacs_control_keys ; 
 scalar_t__ emacs_keys_mode ; 
 scalar_t__ info_type ; 
 int /*<<< orphan*/  info_win ; 
 int /*<<< orphan*/  info_window ; 
 int /*<<< orphan*/  nohighlight ; 
 int /*<<< orphan*/  separator ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wstandend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wstandout (int /*<<< orphan*/ ) ; 

void 
paint_info_win()
{
	int counter;

	if (!info_window)
		return;

	werase(info_win);
	for (counter = 0; counter < 5; counter++)
	{
		wmove(info_win, counter, 0);
		wclrtoeol(info_win);
		if (info_type == CONTROL_KEYS)
			waddstr(info_win, (emacs_keys_mode) ? 
			  emacs_control_keys[counter] : control_keys[counter]);
		else if (info_type == COMMANDS)
			waddstr(info_win, command_strings[counter]);
	}
	wmove(info_win, 5, 0);
	if (!nohighlight)
		wstandout(info_win);
	waddstr(info_win, separator);
	wstandend(info_win);
	wrefresh(info_win);
}