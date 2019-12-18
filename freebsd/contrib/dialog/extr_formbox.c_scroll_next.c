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
struct TYPE_5__ {scalar_t__ name; scalar_t__ text_flen; int /*<<< orphan*/  name_y; int /*<<< orphan*/  text_y; } ;
typedef  TYPE_1__ DIALOG_FORMITEM ;

/* Variables and functions */
 int FALSE ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  beep () ; 
 int form_limit (TYPE_1__*) ; 
 int /*<<< orphan*/  print_item (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  scrollok (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wscrl (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
scroll_next(WINDOW *win, DIALOG_FORMITEM item[], int stepsize, int *choice, int *scrollamt)
{
    bool result = TRUE;
    int old_choice = *choice;
    int old_scroll = *scrollamt;
    int old_row = MIN(item[old_choice].text_y, item[old_choice].name_y);
    int target = old_scroll + stepsize;
    int n;

    if (stepsize < 0) {
	if (old_row != old_scroll)
	    target = old_scroll;
	else
	    target = old_scroll + stepsize;
	if (target < 0) {
	    result = FALSE;
	}
    } else {
	if (target > form_limit(item)) {
	    result = FALSE;
	}
    }

    if (result) {
	for (n = 0; item[n].name != 0; ++n) {
	    if (item[n].text_flen > 0) {
		int new_row = MIN(item[n].text_y, item[n].name_y);
		if (abs(new_row - target) < abs(old_row - target)) {
		    old_row = new_row;
		    *choice = n;
		}
	    }
	}

	if (old_choice != *choice)
	    print_item(win, item + old_choice, *scrollamt, FALSE);

	*scrollamt = *choice;
	if (*scrollamt != old_scroll) {
	    scrollok(win, TRUE);
	    wscrl(win, *scrollamt - old_scroll);
	    scrollok(win, FALSE);
	}
	result = (old_choice != *choice) || (old_scroll != *scrollamt);
    }
    if (!result)
	beep();
    return result;
}