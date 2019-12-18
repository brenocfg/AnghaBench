#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; } ;
struct TYPE_6__ {int line_number; int /*<<< orphan*/  line; } ;
struct TYPE_5__ {char* name; struct TYPE_5__* next_name; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 void* TRUE ; 
 int atoi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cant_open_msg ; 
 void* clear_com_win ; 
 int /*<<< orphan*/  com_win ; 
 TYPE_2__* curr_line ; 
 int /*<<< orphan*/  draw_screen () ; 
 int /*<<< orphan*/  file_is_dir_msg ; 
 int /*<<< orphan*/  file_read_fin_msg ; 
 TYPE_2__* first_line ; 
 int get_fd ; 
 int /*<<< orphan*/  get_file (char*) ; 
 scalar_t__ horiz_offset ; 
 char* in_file_name ; 
 void* input_file ; 
 int /*<<< orphan*/  move_rel (char,int) ; 
 int /*<<< orphan*/  new_file_msg ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  point ; 
 int /*<<< orphan*/  quit (int /*<<< orphan*/ ) ; 
 void* recv_file ; 
 scalar_t__ scr_horz ; 
 scalar_t__ scr_vert ; 
 int /*<<< orphan*/ * start_at_line ; 
 int stat (char*,struct stat*) ; 
 void* text_changes ; 
 int /*<<< orphan*/  text_win ; 
 char* tmp_file ; 
 scalar_t__ tmp_horz ; 
 TYPE_2__* tmp_line ; 
 scalar_t__ tmp_vert ; 
 TYPE_1__* top_of_stack ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

void 
check_fp()		/* open or close files according to flags */
{
	int line_num;
	int temp;
	struct stat buf;

	clear_com_win = TRUE;
	tmp_vert = scr_vert;
	tmp_horz = scr_horz;
	tmp_line = curr_line;
	if (input_file)
	{
		in_file_name = tmp_file = top_of_stack->name;
		top_of_stack = top_of_stack->next_name;
	}
	temp = stat(tmp_file, &buf);
	buf.st_mode &= ~07777;
	if ((temp != -1) && (buf.st_mode != 0100000) && (buf.st_mode != 0))
	{
		wprintw(com_win, file_is_dir_msg, tmp_file);
		wrefresh(com_win);
		if (input_file)
		{
			quit(0);
			return;
		}
		else
			return;
	}
	if ((get_fd = open(tmp_file, O_RDONLY)) == -1)
	{
		wmove(com_win, 0, 0);
		wclrtoeol(com_win);
		if (input_file)
			wprintw(com_win, new_file_msg, tmp_file);
		else
			wprintw(com_win, cant_open_msg, tmp_file);
		wrefresh(com_win);
		wmove(text_win, scr_vert, (scr_horz - horiz_offset));
		wrefresh(text_win);
		recv_file = FALSE;
		input_file = FALSE;
		return;
	}
	else
		get_file(tmp_file);

	recv_file = FALSE;
	line_num = curr_line->line_number;
	scr_vert = tmp_vert;
	scr_horz = tmp_horz;
	if (input_file)
		curr_line= first_line;
	else
		curr_line = tmp_line;
	point = curr_line->line;
	draw_screen();
	if (input_file)
	{
		input_file = FALSE;
		if (start_at_line != NULL)
		{
			line_num = atoi(start_at_line) - 1;
			move_rel('d', line_num);
			line_num = 0;
			start_at_line = NULL;
		}
	}
	else
	{
		wmove(com_win, 0, 0);
		wclrtoeol(com_win);
		text_changes = TRUE;
		if ((tmp_file != NULL) && (*tmp_file != '\0'))
			wprintw(com_win, file_read_fin_msg, tmp_file);
	}
	wrefresh(com_win);
	wmove(text_win, scr_vert, (scr_horz - horiz_offset));
	wrefresh(text_win);
}