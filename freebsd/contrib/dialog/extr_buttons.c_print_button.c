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
typedef  scalar_t__ strspn ;
typedef  int /*<<< orphan*/  chtype ;
typedef  int /*<<< orphan*/  WINDOW ;
typedef  int HOTKEY ;

/* Variables and functions */
 int UCH (char) ; 
 int /*<<< orphan*/  button_active_attr ; 
 int /*<<< orphan*/  button_inactive_attr ; 
 int /*<<< orphan*/  button_key_active_attr ; 
 int /*<<< orphan*/  button_key_inactive_attr ; 
 int /*<<< orphan*/  button_label_active_attr ; 
 int /*<<< orphan*/  button_label_inactive_attr ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dlg_count_wchars (char*) ; 
 int* dlg_index_wchars (char*) ; 
#define  sFIND_KEY 129 
 int sHAD_KEY ; 
#define  sHAVE_KEY 128 
 int string_to_char (char const**) ; 
 int /*<<< orphan*/  waddnstr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
print_button(WINDOW *win, char *label, int hotkey, int y, int x, int selected)
{
    int i;
    HOTKEY state = sFIND_KEY;
    const int *indx = dlg_index_wchars(label);
    int limit = dlg_count_wchars(label);
    chtype key_attr = (selected
		       ? button_key_active_attr
		       : button_key_inactive_attr);
    chtype label_attr = (selected
			 ? button_label_active_attr
			 : button_label_inactive_attr);

    (void) wmove(win, y, x);
    dlg_attrset(win, selected
		? button_active_attr
		: button_inactive_attr);
    (void) waddstr(win, "<");
    dlg_attrset(win, label_attr);
    for (i = 0; i < limit; ++i) {
	int check;
	int first = indx[i];
	int last = indx[i + 1];

	switch (state) {
	case sFIND_KEY:
	    check = UCH(label[first]);
#ifdef USE_WIDE_CURSES
	    if ((last - first) != 1) {
		const char *temp = (label + first);
		check = string_to_char(&temp);
	    }
#endif
	    if (check == hotkey) {
		dlg_attrset(win, key_attr);
		state = sHAVE_KEY;
	    }
	    break;
	case sHAVE_KEY:
	    dlg_attrset(win, label_attr);
	    state = sHAD_KEY;
	    break;
	default:
	    break;
	}
	waddnstr(win, label + first, last - first);
    }
    dlg_attrset(win, selected
		? button_active_attr
		: button_inactive_attr);
    (void) waddstr(win, ">");
    (void) wmove(win, y, x + ((int) (strspn) (label, " ")) + 1);
}