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
 int ERR ; 
 int KEY_RESIZE ; 
 int /*<<< orphan*/  dlg_trace_msg (char*,int,char*) ; 
 int /*<<< orphan*/  dlg_trace_win (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ungetch (int) ; 
 int wgetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wtimeout (int /*<<< orphan*/ *,int) ; 

void
dlg_will_resize(WINDOW *win)
{
    int n, ch, base;
    int caught = 0;

    dlg_trace_win(win);
    wtimeout(win, 20);
    for (n = base = 0; n < base + 10; ++n) {
	if ((ch = wgetch(win)) != ERR) {
	    if (ch == KEY_RESIZE) {
		base = n;
		++caught;
	    } else {
		ungetch(ch);
		break;
	    }
	}
    }
    dlg_trace_msg("# caught %d KEY_RESIZE key%s\n",
		  1 + caught,
		  caught == 1 ? "" : "s");
}