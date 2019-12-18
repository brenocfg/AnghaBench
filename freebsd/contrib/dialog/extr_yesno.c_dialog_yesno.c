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
#define  DLGK_ENTER 136 
#define  DLGK_FIELD_NEXT 135 
#define  DLGK_FIELD_PREV 134 
 int DLG_EXIT_OK ; 
 int DLG_EXIT_UNKNOWN ; 
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
 int /*<<< orphan*/  DLG_TRACE2N (char*,int) ; 
 int /*<<< orphan*/  DLG_TRACE2S (char*,char const*) ; 
#define  END_KEYS_BINDING 133 
#define  ENTERKEY_BINDINGS 132 
 int FALSE ; 
#define  HELPKEY_BINDINGS 131 
#define  KEY_RESIZE 130 
 int MARGIN ; 
 int /*<<< orphan*/  M_EVENT ; 
#define  SCROLLKEY_BINDINGS 129 
#define  TRAVERSE_BINDINGS 128 
 int TRUE ; 
 int /*<<< orphan*/  beep () ; 
 int /*<<< orphan*/  border2_attr ; 
 int /*<<< orphan*/  border_attr ; 
 int /*<<< orphan*/  dialog_attr ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_auto_size (char const*,char*,int*,int*,int,int) ; 
 int dlg_box_x_ordinate (int) ; 
 int dlg_box_y_ordinate (int) ; 
 int /*<<< orphan*/  dlg_button_layout (char const**,int*) ; 
 int dlg_char_to_button (int,char const**) ; 
 int /*<<< orphan*/  dlg_check_scrolled (int,int,int,int*,int*) ; 
 int /*<<< orphan*/  dlg_clear () ; 
 int /*<<< orphan*/  dlg_ctl_size (int,int) ; 
 int dlg_default_button () ; 
 int /*<<< orphan*/  dlg_del_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_draw_bottom_box2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_box2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_buttons (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char const**,int,int,int) ; 
 int /*<<< orphan*/  dlg_draw_helpline (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dlg_draw_title (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  dlg_mouse_free_regions () ; 
 int dlg_mouse_wgetch (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  dlg_move_window (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/ * dlg_new_window (int,int,int,int) ; 
 int dlg_next_button (char const**,int) ; 
 int dlg_ok_buttoncode (int) ; 
 int dlg_prev_button (char const**,int) ; 
 int dlg_print_scrolled (int /*<<< orphan*/ *,char*,int,int,int,int) ; 
 int /*<<< orphan*/  dlg_print_size (int,int) ; 
 int /*<<< orphan*/  dlg_register_buttons (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/  dlg_register_window (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ dlg_result_key (int,int,int*) ; 
 char* dlg_strclone (char const*) ; 
 int /*<<< orphan*/  dlg_tab_correct_str (char*) ; 
 int /*<<< orphan*/  dlg_trace_win (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_will_resize (int /*<<< orphan*/ *) ; 
 int dlg_yes_buttoncode (int) ; 
 char** dlg_yes_labels () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_DLGK_MOUSE (int) ; 

int
dialog_yesno(const char *title, const char *cprompt, int height, int width)
{
    /* *INDENT-OFF* */
    static DLG_KEYS_BINDING binding[] = {
	HELPKEY_BINDINGS,
	ENTERKEY_BINDINGS,
	SCROLLKEY_BINDINGS,
	TRAVERSE_BINDINGS,
	END_KEYS_BINDING
    };
    /* *INDENT-ON* */

    int x, y;
    int key = 0, fkey;
    int code;
    int button = dlg_default_button();
    WINDOW *dialog = 0;
    int result = DLG_EXIT_UNKNOWN;
    char *prompt;
    const char **buttons = dlg_yes_labels();
    int min_width = 25;
    bool show = TRUE;
    int page, last = 0, offset = 0;

#ifdef KEY_RESIZE
    int req_high = height;
    int req_wide = width;
#endif

    DLG_TRACE(("# yesno args:\n"));
    DLG_TRACE2S("title", title);
    DLG_TRACE2S("message", cprompt);
    DLG_TRACE2N("height", height);
    DLG_TRACE2N("width", width);

#ifdef KEY_RESIZE
  restart:
#endif
    prompt = dlg_strclone(cprompt);
    dlg_tab_correct_str(prompt);
    dlg_button_layout(buttons, &min_width);
    dlg_auto_size(title, prompt, &height, &width, 2, min_width);
    dlg_print_size(height, width);
    dlg_ctl_size(height, width);

    x = dlg_box_x_ordinate(width);
    y = dlg_box_y_ordinate(height);

#ifdef KEY_RESIZE
    if (dialog != 0)
	dlg_move_window(dialog, height, width, y, x);
    else
#endif
    {
	dialog = dlg_new_window(height, width, y, x);
	dlg_register_window(dialog, "yesno", binding);
	dlg_register_buttons(dialog, "yesno", buttons);
    }

    dlg_draw_box2(dialog, 0, 0, height, width, dialog_attr, border_attr, border2_attr);
    dlg_draw_bottom_box2(dialog, border_attr, border2_attr, dialog_attr);
    dlg_draw_title(dialog, title);
    dlg_draw_helpline(dialog, FALSE);

    dlg_attrset(dialog, dialog_attr);

    page = height - (1 + 3 * MARGIN);
    dlg_draw_buttons(dialog,
		     height - 2 * MARGIN, 0,
		     buttons, button, FALSE, width);

    while (result == DLG_EXIT_UNKNOWN) {
	if (show) {
	    last = dlg_print_scrolled(dialog, prompt, offset,
				      page, width, TRUE);
	    dlg_trace_win(dialog);
	    show = FALSE;
	}
	key = dlg_mouse_wgetch(dialog, &fkey);
	if (dlg_result_key(key, fkey, &result))
	    break;
	if ((code = dlg_char_to_button(key, buttons)) >= 0) {
	    result = dlg_ok_buttoncode(code);
	    break;
	}
	/* handle function keys */
	if (fkey) {
	    switch (key) {
	    case DLGK_FIELD_NEXT:
		button = dlg_next_button(buttons, button);
		if (button < 0)
		    button = 0;
		dlg_draw_buttons(dialog,
				 height - 2, 0,
				 buttons, button,
				 FALSE, width);
		break;
	    case DLGK_FIELD_PREV:
		button = dlg_prev_button(buttons, button);
		if (button < 0)
		    button = 0;
		dlg_draw_buttons(dialog,
				 height - 2, 0,
				 buttons, button,
				 FALSE, width);
		break;
	    case DLGK_ENTER:
		result = dlg_yes_buttoncode(button);
		break;
#ifdef KEY_RESIZE
	    case KEY_RESIZE:
		dlg_will_resize(dialog);
		dlg_clear();
		free(prompt);
		height = req_high;
		width = req_wide;
		show = TRUE;
		goto restart;
#endif
	    default:
		if (is_DLGK_MOUSE(key)) {
		    result = dlg_yes_buttoncode(key - M_EVENT);
		    if (result < 0)
			result = DLG_EXIT_OK;
		} else if (dlg_check_scrolled(key, last, page,
					      &show, &offset) != 0) {
		    beep();
		}
		break;
	    }
	} else {
	    beep();
	}
    }

    dlg_del_window(dialog);
    dlg_mouse_free_regions();
    free(prompt);
    return result;
}