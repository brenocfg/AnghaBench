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
typedef  int /*<<< orphan*/  DLG_KEYS_BINDING ;

/* Variables and functions */
#define  DLGK_ENTER 133 
 int DLG_EXIT_CANCEL ; 
 int DLG_EXIT_ESC ; 
 int DLG_EXIT_OK ; 
 int DLG_EXIT_UNKNOWN ; 
#define  END_KEYS_BINDING 132 
#define  ENTERKEY_BINDINGS 131 
 int ERR ; 
 int ESC ; 
 int FALSE ; 
#define  HELPKEY_BINDINGS 130 
#define  INPUTSTR_BINDINGS 129 
#define  KEY_RESIZE 128 
 int MARGIN ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dlg_count_columns (char const*) ; 
 int /*<<< orphan*/  dlg_del_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_draw_box2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dlg_edit_string (char*,int*,int,int,int) ; 
 int dlg_getc (int /*<<< orphan*/ *,int*) ; 
 int* dlg_index_wchars (char const*) ; 
 int dlg_limit_columns (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dlg_new_modal_window (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  dlg_register_window (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_show_string (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  getbegyx (int /*<<< orphan*/ *,int,int) ; 
 int getmaxx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  napms (int) ; 
 int /*<<< orphan*/  searchbox_attr ; 
 int /*<<< orphan*/  searchbox_border2_attr ; 
 int /*<<< orphan*/  searchbox_border_attr ; 
 int /*<<< orphan*/  searchbox_title_attr ; 
 int /*<<< orphan*/  waddnstr (int /*<<< orphan*/ *,char const*,int const) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
get_search_term(WINDOW *dialog, char *input, int height, int width)
{
    /* *INDENT-OFF* */
    static DLG_KEYS_BINDING binding[] = {
	INPUTSTR_BINDINGS,
	HELPKEY_BINDINGS,
	ENTERKEY_BINDINGS,
	END_KEYS_BINDING
    };
    /* *INDENT-ON* */

    int old_x, old_y;
    int box_x, box_y;
    int box_height, box_width;
    int offset = 0;
    int key = 0;
    int fkey = 0;
    bool first = TRUE;
    int result = DLG_EXIT_UNKNOWN;
    const char *caption = _("Search");
    int len_caption = dlg_count_columns(caption);
    const int *indx;
    int limit;
    WINDOW *widget;

    getbegyx(dialog, old_y, old_x);

    box_height = 1 + (2 * MARGIN);
    box_width = len_caption + (2 * (MARGIN + 2));
    box_width = MAX(box_width, 30);
    box_width = MIN(box_width, getmaxx(dialog) - 2 * MARGIN);
    len_caption = MIN(len_caption, box_width - (2 * (MARGIN + 1)));

    box_x = (width - box_width) / 2;
    box_y = (height - box_height) / 2;
    widget = dlg_new_modal_window(dialog,
				  box_height, box_width,
				  old_y + box_y, old_x + box_x);
    keypad(widget, TRUE);
    dlg_register_window(widget, "searchbox", binding);

    dlg_draw_box2(widget, 0, 0, box_height, box_width,
		  searchbox_attr,
		  searchbox_border_attr,
		  searchbox_border2_attr);
    dlg_attrset(widget, searchbox_title_attr);
    (void) wmove(widget, 0, (box_width - len_caption) / 2);

    indx = dlg_index_wchars(caption);
    limit = dlg_limit_columns(caption, len_caption, 0);
    (void) waddnstr(widget, caption + indx[0], indx[limit] - indx[0]);

    box_width -= 2;
    offset = dlg_count_columns(input);

    while (result == DLG_EXIT_UNKNOWN) {
	if (!first) {
	    key = dlg_getc(widget, &fkey);
	    if (fkey) {
		switch (fkey) {
#ifdef KEY_RESIZE
		case KEY_RESIZE:
		    result = DLG_EXIT_CANCEL;
		    continue;
#endif
		case DLGK_ENTER:
		    result = DLG_EXIT_OK;
		    continue;
		}
	    } else if (key == ESC) {
		result = DLG_EXIT_ESC;
		continue;
	    } else if (key == ERR) {
		napms(50);
		continue;
	    }
	}
	if (dlg_edit_string(input, &offset, key, fkey, first)) {
	    dlg_show_string(widget, input, offset, searchbox_attr,
			    1, 1, box_width, FALSE, first);
	    first = FALSE;
	}
    }
    dlg_del_window(widget);
    return result;
}