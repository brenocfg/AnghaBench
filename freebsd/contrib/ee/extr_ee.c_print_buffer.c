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
 int /*<<< orphan*/  com_win ; 
 int /*<<< orphan*/  command (char*) ; 
 char* print_command ; 
 int /*<<< orphan*/  printer_msg_str ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

void 
print_buffer()
{
	char buffer[256];

	sprintf(buffer, ">!%s", print_command);
	wmove(com_win, 0, 0);
	wclrtoeol(com_win);
	wprintw(com_win, printer_msg_str, print_command);
	wrefresh(com_win);
	command(buffer);
}