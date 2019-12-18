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
 int /*<<< orphan*/  COMMANDS ; 
 int /*<<< orphan*/  CONTROL_KEYS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  com_win ; 
 int /*<<< orphan*/  command (char*) ; 
 int /*<<< orphan*/  command_str ; 
 int /*<<< orphan*/  commands ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ horiz_offset ; 
 int /*<<< orphan*/  info_type ; 
 int /*<<< orphan*/  non_unique_cmd_msg ; 
 int /*<<< orphan*/  paint_info_win () ; 
 scalar_t__ scr_horz ; 
 int /*<<< orphan*/  scr_vert ; 
 int /*<<< orphan*/  text_win ; 
 int unique_test (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unkn_cmd_str ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

void 
command_prompt()
{
	char *cmd_str;
	int result;

	info_type = COMMANDS;
	paint_info_win();
	cmd_str = get_string(command_str, TRUE);
	if ((result = unique_test(cmd_str, commands)) != 1)
	{
		werase(com_win);
		wmove(com_win, 0, 0);
		if (result == 0)
			wprintw(com_win, unkn_cmd_str, cmd_str);
		else
			wprintw(com_win, non_unique_cmd_msg);

		wrefresh(com_win);

		info_type = CONTROL_KEYS;
		paint_info_win();

		if (cmd_str != NULL)
			free(cmd_str);
		return;
	}
	command(cmd_str);
	wrefresh(com_win);
	wmove(text_win, scr_vert, (scr_horz - horiz_offset));
	info_type = CONTROL_KEYS;
	paint_info_win();
	if (cmd_str != NULL)
		free(cmd_str);
}