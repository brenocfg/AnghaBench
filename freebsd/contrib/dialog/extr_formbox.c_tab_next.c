#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_5__ {scalar_t__ text_flen; int /*<<< orphan*/  text_y; int /*<<< orphan*/  name_y; } ;
typedef  TYPE_1__ DIALOG_FORMITEM ;

/* Variables and functions */
 int FALSE ; 
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  beep () ; 
 int getmaxy (int /*<<< orphan*/ *) ; 
 scalar_t__ is_readonly (TYPE_1__*) ; 
 int /*<<< orphan*/  print_item (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  scrollok (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wscrl (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
tab_next(WINDOW *win,
	 DIALOG_FORMITEM item[],
	 int item_no,
	 int stepsize,
	 int *choice,
	 int *scrollamt)
{
    int old_choice = *choice;
    int old_scroll = *scrollamt;
    bool wrapped = FALSE;

    do {
	do {
	    *choice += stepsize;
	    if (*choice < 0) {
		*choice = item_no - 1;
		wrapped = TRUE;
	    } else if (*choice >= item_no) {
		*choice = 0;
		wrapped = TRUE;
	    }
	} while ((*choice != old_choice) && is_readonly(&(item[*choice])));

	if (item[*choice].text_flen > 0) {
	    int lo = MIN(item[*choice].name_y, item[*choice].text_y);
	    int hi = MAX(item[*choice].name_y, item[*choice].text_y);

	    if (old_choice == *choice)
		break;
	    print_item(win, item + old_choice, *scrollamt, FALSE);

	    if (*scrollamt < lo + 1 - getmaxy(win))
		*scrollamt = lo + 1 - getmaxy(win);
	    if (*scrollamt > hi)
		*scrollamt = hi;
	    /*
	     * If we have to scroll to show a wrap-around, it does get
	     * confusing.  Just give up rather than scroll.  Tab'ing to the
	     * next field in a multi-column form is a different matter.  Scroll
	     * for that.
	     */
	    if (*scrollamt != old_scroll) {
		if (wrapped) {
		    beep();
		    *scrollamt = old_scroll;
		    *choice = old_choice;
		} else {
		    scrollok(win, TRUE);
		    wscrl(win, *scrollamt - old_scroll);
		    scrollok(win, FALSE);
		}
	    }
	    break;
	}
    } while (*choice != old_choice);

    return (old_choice != *choice) || (old_scroll != *scrollamt);
}