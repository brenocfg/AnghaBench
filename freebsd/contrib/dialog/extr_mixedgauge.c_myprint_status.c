#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int chtype ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_5__ {int height; int width; int len_text; int item_no; TYPE_1__* list; int /*<<< orphan*/ * dialog; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  text; } ;
typedef  TYPE_2__ DIALOG_MIXEDGAUGE ;

/* Variables and functions */
 int A_NORMAL ; 
 int A_REVERSE ; 
 int MARGIN ; 
 int dialog_attr ; 
 int /*<<< orphan*/  dlg_attroff (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dlg_print_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 int sscanf (char const*,char*,float*) ; 
 char* status_string (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ strlen (char const*) ; 
 int title_attr ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ *,char const*) ; 
 int winch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
myprint_status(DIALOG_MIXEDGAUGE * dlg)
{
    WINDOW *win = dlg->dialog;
    int limit_y = dlg->height;
    int limit_x = dlg->width;

    int y = MARGIN;
    int item;
    int cells = dlg->len_text - 2;
    int lm = limit_x - dlg->len_text - 1;
    int bm = limit_y;		/* bottom margin */
    int last_y = 0, last_x = 0;
    int j, xxx;
    float percent;
    const char *status = "";
    char *freeMe = 0;

    bm -= (2 * MARGIN);
    getyx(win, last_y, last_x);
    for (item = 0; item < dlg->item_no; ++item) {
	chtype attr = A_NORMAL;

	y = item + MARGIN + 1;
	if (y > bm)
	    break;

	status = status_string(dlg->list[item].text, &freeMe);
	if (status == 0 || *status == 0)
	    continue;

	(void) wmove(win, y, 2 * MARGIN);
	dlg_attrset(win, dialog_attr);
	dlg_print_text(win, dlg->list[item].name, lm, &attr);

	(void) wmove(win, y, lm);
	(void) waddch(win, '[');
	(void) wmove(win, y, lm + (cells - (int) strlen(status)) / 2);
	if (freeMe) {
	    (void) wmove(win, y, lm + 1);
	    dlg_attrset(win, title_attr);
	    for (j = 0; j < cells; j++)
		(void) waddch(win, ' ');

	    (void) wmove(win, y, lm + (cells - (int) strlen(status)) / 2);
	    (void) waddstr(win, status);

	    if ((title_attr & A_REVERSE) != 0) {
		dlg_attroff(win, A_REVERSE);
	    } else {
		dlg_attrset(win, A_REVERSE);
	    }
	    (void) wmove(win, y, lm + 1);

	    if (sscanf(status, "%f%%", &percent) != 1)
		percent = 0.0;
	    xxx = (int) ((cells * (percent + 0.5)) / 100.0);
	    for (j = 0; j < xxx; j++) {
		chtype ch1 = winch(win);
		if (title_attr & A_REVERSE) {
		    ch1 &= ~A_REVERSE;
		}
		(void) waddch(win, ch1);
	    }
	    free(freeMe);

	} else {
	    (void) wmove(win, y, lm + (cells - (int) strlen(status)) / 2);
	    (void) waddstr(win, status);
	}
	(void) wmove(win, y, limit_x - 3);
	dlg_attrset(win, dialog_attr);
	(void) waddch(win, ']');
	(void) wnoutrefresh(win);
    }
    if (win != 0)
	wmove(win, last_y, last_x);
}