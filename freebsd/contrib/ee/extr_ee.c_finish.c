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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  clear_com_win ; 
 int /*<<< orphan*/  com_win ; 
 int /*<<< orphan*/  file_not_saved_msg ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* in_file_name ; 
 int /*<<< orphan*/  quit (int /*<<< orphan*/ ) ; 
 char* resolve_name (char*) ; 
 int /*<<< orphan*/  save_file_name_prompt ; 
 int /*<<< orphan*/  text_changes ; 
 char* tmp_file ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 
 scalar_t__ write_file (char*,int) ; 

void 
finish()	/* prepare to exit edit session	*/
{
	char *file_name = in_file_name;

	/*
	 |	changes made here should be reflected in the 'save' 
	 |	portion of file_op()
	 */

	if ((file_name == NULL) || (*file_name == '\0'))
		file_name = get_string(save_file_name_prompt, TRUE);

	if ((file_name == NULL) || (*file_name == '\0'))
	{
		wmove(com_win, 0, 0);
		wprintw(com_win, file_not_saved_msg);
		wclrtoeol(com_win);
		wrefresh(com_win);
		clear_com_win = TRUE;
		return;
	}

	tmp_file = resolve_name(file_name);
	if (tmp_file != file_name)
	{
		free(file_name);
		file_name = tmp_file;
	}

	if (write_file(file_name, 1))
	{
		text_changes = FALSE;
		quit(0);
	}
}