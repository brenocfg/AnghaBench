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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_fp () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  com_win ; 
 int /*<<< orphan*/  create_file_fail_msg ; 
 int /*<<< orphan*/  delete_text () ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  recv_file ; 
 scalar_t__ restrict_mode () ; 
 int /*<<< orphan*/  sh_command (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 char* tmp_file ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 
 scalar_t__ write_file (char*,int /*<<< orphan*/ ) ; 

void 
ispell_op()
{
	char template[128], *name;
	char string[256];
	int fd;

	if (restrict_mode())
	{
		return;
	}
	(void)sprintf(template, "/tmp/ee.XXXXXXXX");
	fd = mkstemp(template);
	if (fd < 0) {
		wmove(com_win, 0, 0);
		wprintw(com_win, create_file_fail_msg, name);
		wrefresh(com_win);
		return;
	}
	close(fd);
	if (write_file(name, 0))
	{
		sprintf(string, "ispell %s", name);
		sh_command(string);
		delete_text();
		tmp_file = name;
		recv_file = TRUE;
		check_fp();
		unlink(name);
	}
}