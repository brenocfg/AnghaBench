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
 int /*<<< orphan*/  COLS ; 
 scalar_t__ FALSE ; 
 scalar_t__ LINES ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  clear_com_win ; 
 int /*<<< orphan*/  clearok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idlok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info_win ; 
 scalar_t__ info_window ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ last_line ; 
 int /*<<< orphan*/  midscreen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newwin (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  point ; 
 int /*<<< orphan*/  scr_vert ; 
 int /*<<< orphan*/  text_win ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

void 
no_info_window()
{
	if (!info_window)
		return;
	delwin(info_win);
	delwin(text_win);
	info_window = FALSE;
	last_line = LINES - 2;
	text_win = newwin((LINES - 1), COLS, 0, 0);
	keypad(text_win, TRUE);
	idlok(text_win, TRUE);
	clearok(text_win, TRUE);
	midscreen(scr_vert, point);
	wrefresh(text_win);
	clear_com_win = TRUE;
}