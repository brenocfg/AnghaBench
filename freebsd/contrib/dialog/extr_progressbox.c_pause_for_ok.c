#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nocancel; } ;
struct TYPE_8__ {int /*<<< orphan*/  win; } ;
struct TYPE_9__ {TYPE_1__ obj; int /*<<< orphan*/  wide; scalar_t__ high; } ;
typedef  TYPE_2__ MY_OBJ ;
typedef  int /*<<< orphan*/  DLG_KEYS_BINDING ;

/* Variables and functions */
#define  DLGK_ENTER 135 
#define  DLGK_FIELD_NEXT 134 
#define  DLGK_FIELD_PREV 133 
 int DLG_EXIT_OK ; 
 int DLG_EXIT_UNKNOWN ; 
#define  END_KEYS_BINDING 132 
#define  ENTERKEY_BINDINGS 131 
 int FALSE ; 
#define  HELPKEY_BINDINGS 130 
#define  KEY_RESIZE 129 
 int /*<<< orphan*/  M_EVENT ; 
#define  TRAVERSE_BINDINGS 128 
 void* TRUE ; 
 int /*<<< orphan*/  beep () ; 
 int /*<<< orphan*/  border2_attr ; 
 int /*<<< orphan*/  border_attr ; 
 int /*<<< orphan*/  dialog_attr ; 
 TYPE_7__ dialog_vars ; 
 int dlg_char_to_button (int,char const**) ; 
 int dlg_default_button () ; 
 int /*<<< orphan*/  dlg_draw_bottom_box2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_buttons (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char const**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_mouse_free_regions () ; 
 int dlg_mouse_wgetch (int /*<<< orphan*/ ,int*) ; 
 int dlg_next_button (char const**,int) ; 
 int dlg_ok_buttoncode (int) ; 
 char** dlg_ok_label () ; 
 int dlg_prev_button (char const**,int) ; 
 int /*<<< orphan*/  dlg_register_buttons (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  dlg_register_window (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ dlg_result_key (int,int,int*) ; 
 int /*<<< orphan*/  dlg_unregister_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_will_resize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_DLGK_MOUSE (int) ; 
 int /*<<< orphan*/  reprint_lines (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  restart_obj (TYPE_2__*) ; 
 int /*<<< orphan*/  start_obj (TYPE_2__*,char const*,char const*) ; 

__attribute__((used)) static int
pause_for_ok(MY_OBJ * obj, const char *title, const char *cprompt)
{
    /* *INDENT-OFF* */
    static DLG_KEYS_BINDING binding[] = {
	HELPKEY_BINDINGS,
	ENTERKEY_BINDINGS,
	TRAVERSE_BINDINGS,
	END_KEYS_BINDING
    };
    /* *INDENT-ON* */

    int button;
    int key = 0, fkey;
    int result = DLG_EXIT_UNKNOWN;
    const char **buttons = dlg_ok_label();
    int check;
    bool save_nocancel = dialog_vars.nocancel;
    bool redraw = TRUE;

    dialog_vars.nocancel = TRUE;
    button = dlg_default_button();

#ifdef KEY_RESIZE
  restart:
#endif

    dlg_register_window(obj->obj.win, "progressbox", binding);
    dlg_register_buttons(obj->obj.win, "progressbox", buttons);

    dlg_draw_bottom_box2(obj->obj.win, border_attr, border2_attr, dialog_attr);

    while (result == DLG_EXIT_UNKNOWN) {
	if (redraw) {
	    redraw = FALSE;
	    if (button < 0)
		button = 0;
	    dlg_draw_buttons(obj->obj.win,
			     obj->high - 2, 0,
			     buttons, button,
			     FALSE, obj->wide);
	}

	key = dlg_mouse_wgetch(obj->obj.win, &fkey);
	if (dlg_result_key(key, fkey, &result))
	    break;

	if (!fkey && (check = dlg_char_to_button(key, buttons)) >= 0) {
	    result = dlg_ok_buttoncode(check);
	    break;
	}

	if (fkey) {
	    switch (key) {
	    case DLGK_FIELD_NEXT:
		button = dlg_next_button(buttons, button);
		redraw = TRUE;
		break;
	    case DLGK_FIELD_PREV:
		button = dlg_prev_button(buttons, button);
		redraw = TRUE;
		break;
	    case DLGK_ENTER:
		result = dlg_ok_buttoncode(button);
		break;
#ifdef KEY_RESIZE
	    case KEY_RESIZE:
		dlg_will_resize(obj->obj.win);
		restart_obj(obj);
		start_obj(obj, title, cprompt);
		reprint_lines(obj, TRUE);
		redraw = TRUE;
		goto restart;
#endif
	    default:
		if (is_DLGK_MOUSE(key)) {
		    result = dlg_ok_buttoncode(key - M_EVENT);
		    if (result < 0)
			result = DLG_EXIT_OK;
		} else {
		    beep();
		}
		break;
	    }

	} else {
	    beep();
	}
    }
    dlg_mouse_free_regions();
    dlg_unregister_window(obj->obj.win);

    dialog_vars.nocancel = save_nocancel;
    return result;
}