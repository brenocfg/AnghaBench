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
typedef  int /*<<< orphan*/  chtype ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  ACS_HLINE ; 
 int /*<<< orphan*/  ACS_LTEE ; 
 int /*<<< orphan*/  ACS_RTEE ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char dlg_boxchar (int /*<<< orphan*/ ) ; 
 int getmaxx (int /*<<< orphan*/ *) ; 
 int getmaxy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 

void
dlg_draw_bottom_box2(WINDOW *win, chtype on_left, chtype on_right, chtype on_inside)
{
    int width = getmaxx(win);
    int height = getmaxy(win);
    int i;

    dlg_attrset(win, on_left);
    (void) wmove(win, height - 3, 0);
    (void) waddch(win, dlg_boxchar(ACS_LTEE));
    for (i = 0; i < width - 2; i++)
	(void) waddch(win, dlg_boxchar(ACS_HLINE));
    dlg_attrset(win, on_right);
    (void) waddch(win, dlg_boxchar(ACS_RTEE));
    dlg_attrset(win, on_inside);
    (void) wmove(win, height - 2, 1);
    for (i = 0; i < width - 2; i++)
	(void) waddch(win, ' ');
}