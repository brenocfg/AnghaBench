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
 char* get_line (char const*,int) ; 
 int get_line_length (char const*) ; 
 int get_line_no (char const*) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ *,int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

void fill_window(WINDOW *win, const char *text)
{
	int x, y;
	int total_lines = get_line_no(text);
	int i;

	getmaxyx(win, y, x);
	/* do not go over end of line */
	total_lines = min(total_lines, y);
	for (i = 0; i < total_lines; i++) {
		char tmp[x+10];
		const char *line = get_line(text, i);
		int len = get_line_length(line);
		strncpy(tmp, line, min(len, x));
		tmp[len] = '\0';
		mvwprintw(win, i, 0, "%s", tmp);
	}
}