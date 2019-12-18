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
 int /*<<< orphan*/  CONTROL_KEYS ; 
 int LINES ; 
 void* TRUE ; 
 void* clear_com_win ; 
 int /*<<< orphan*/  clearok (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idlok (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  info_type ; 
 int /*<<< orphan*/  info_win ; 
 void* info_window ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,void*) ; 
 int last_line ; 
 int /*<<< orphan*/  midscreen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  newwin (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paint_info_win () ; 
 int /*<<< orphan*/  point ; 
 int /*<<< orphan*/  scr_vert ; 
 int /*<<< orphan*/  text_win ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

void 
create_info_window()
{
	if (info_window)
		return;
	last_line = LINES - 8;
	delwin(text_win);
	text_win = newwin((LINES - 7), COLS, 6, 0);
	keypad(text_win, TRUE);
	idlok(text_win, TRUE);
	werase(text_win);
	info_window = TRUE;
	info_win = newwin(6, COLS, 0, 0);
	werase(info_win);
	info_type = CONTROL_KEYS;
	midscreen(min(scr_vert, last_line), point);
	clearok(info_win, TRUE);
	paint_info_win();
	wrefresh(text_win);
	clear_com_win = TRUE;
}