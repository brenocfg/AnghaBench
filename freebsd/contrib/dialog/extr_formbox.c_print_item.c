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
typedef  int /*<<< orphan*/  chtype ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_5__ {int name_len; int text_len; scalar_t__ text_x; scalar_t__ text_y; int /*<<< orphan*/  text; scalar_t__ name_x; scalar_t__ name_y; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ DIALOG_FORMITEM ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  dlg_show_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  form_active_text_attr ; 
 int /*<<< orphan*/  form_item_readonly_attr ; 
 int /*<<< orphan*/  form_text_attr ; 
 scalar_t__ getmaxx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_hidden (TYPE_1__*) ; 
 int /*<<< orphan*/  is_readonly (TYPE_1__*) ; 
 int /*<<< orphan*/  menubox_attr ; 
 int /*<<< orphan*/  move_past (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ ok_move (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
print_item(WINDOW *win, DIALOG_FORMITEM * item, int scrollamt, bool choice)
{
    int count = 0;
    int len;

    if (ok_move(win, scrollamt, item->name_y, item->name_x)) {
	len = item->name_len;
	len = MIN(len, getmaxx(win) - item->name_x);
	if (len > 0) {
	    dlg_show_string(win,
			    item->name,
			    0,
			    menubox_attr,
			    item->name_y - scrollamt,
			    item->name_x,
			    len,
			    FALSE,
			    FALSE);
	    move_past(win, item->name_y - scrollamt, item->name_x + len);
	    count = 1;
	}
    }
    if (item->text_len && ok_move(win, scrollamt, item->text_y, item->text_x)) {
	chtype this_item_attribute;

	len = item->text_len;
	len = MIN(len, getmaxx(win) - item->text_x);

	if (!is_readonly(item)) {
	    this_item_attribute = choice
		? form_active_text_attr
		: form_text_attr;
	} else {
	    this_item_attribute = form_item_readonly_attr;
	}

	if (len > 0) {
	    dlg_show_string(win,
			    item->text,
			    0,
			    this_item_attribute,
			    item->text_y - scrollamt,
			    item->text_x,
			    len,
			    is_hidden(item),
			    FALSE);
	    move_past(win, item->text_y - scrollamt, item->text_x + len);
	    count = 1;
	}
    }
    return count;
}