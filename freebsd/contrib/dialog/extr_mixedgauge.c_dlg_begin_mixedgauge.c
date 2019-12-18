#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  text; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {char const* title; scalar_t__* prompt; int height; int old_height; int width; int old_width; int item_no; int len_name; int len_text; int min_width; int /*<<< orphan*/  dialog; int /*<<< orphan*/  caption; scalar_t__ min_height; TYPE_3__* list; } ;
typedef  TYPE_1__ DIALOG_MIXEDGAUGE ;

/* Variables and functions */
 int /*<<< orphan*/  DIALOG_LISTITEM ; 
 scalar_t__ ERR ; 
 int /*<<< orphan*/  FALSE ; 
 int GUTTER ; 
 int /*<<< orphan*/  ItemName (int) ; 
 int /*<<< orphan*/  ItemText (int) ; 
 int MARGIN ; 
 scalar_t__ MIN_HIGH ; 
 int MIN_WIDE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert_ptr (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  border2_attr ; 
 int /*<<< orphan*/  border_attr ; 
 scalar_t__* clean_copy (char const*) ; 
 int /*<<< orphan*/  curs_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dialog_attr ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_auto_size (char const*,scalar_t__*,int*,int*,scalar_t__,int) ; 
 int dlg_box_x_ordinate (int) ; 
 int dlg_box_y_ordinate (int) ; 
 TYPE_3__* dlg_calloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dlg_ctl_size (int,int) ; 
 int /*<<< orphan*/  dlg_del_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_box2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_helpline (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_title (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dlg_new_window (int,int,int,int) ; 
 int /*<<< orphan*/  dlg_print_autowrap (int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  dlg_print_size (int,int) ; 
 int /*<<< orphan*/  dlg_sub_window (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mydraw_mixed_box (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodelay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdscr ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 
 scalar_t__ wmove (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dlg_begin_mixedgauge(DIALOG_MIXEDGAUGE * dlg,
		     int *began,
		     const char *aTitle,
		     const char *aPrompt,
		     int aHeight,
		     int aWidth,
		     int aItemNo,
		     char **items)
{
    int n, y, x;

    if (!*began) {
	curs_set(0);

	memset(dlg, 0, sizeof(*dlg));
	dlg->title = aTitle;
	dlg->prompt = clean_copy(aPrompt);
	dlg->height = dlg->old_height = aHeight;
	dlg->width = dlg->old_width = aWidth;
	dlg->item_no = aItemNo;

	dlg->list = dlg_calloc(DIALOG_LISTITEM, (size_t) aItemNo);
	assert_ptr(dlg->list, "dialog_mixedgauge");

	dlg->len_name = 0;
	dlg->len_text = 15;

	for (n = 0; n < aItemNo; ++n) {
	    int thisWidth = (int) strlen(ItemName(n));
	    if (dlg->len_name < thisWidth)
		dlg->len_name = thisWidth;
	    dlg->list[n].name = ItemName(n);
	    dlg->list[n].text = ItemText(n);
	}

	dlg->min_height = MIN_HIGH + aItemNo;
	dlg->min_width = MIN_WIDE + dlg->len_name + GUTTER + dlg->len_text;

	if (dlg->prompt != 0 && *(dlg->prompt) != 0)
	    dlg->min_height += (2 * MARGIN);
#ifdef KEY_RESIZE
	nodelay(stdscr, TRUE);
#endif
    }
#ifdef KEY_RESIZE
    else {
	dlg_del_window(dlg->dialog);
	dlg->height = dlg->old_height;
	dlg->width = dlg->old_width;
    }
#endif

    dlg_auto_size(dlg->title, dlg->prompt,
		  &(dlg->height),
		  &(dlg->width),
		  dlg->min_height,
		  dlg->min_width);
    dlg_print_size(dlg->height, dlg->width);
    dlg_ctl_size(dlg->height, dlg->width);

    /* center dialog box on screen */
    x = dlg_box_x_ordinate(dlg->width);
    y = dlg_box_y_ordinate(dlg->height);

    dlg->dialog = dlg_new_window(dlg->height, dlg->width, y, x);

    (void) werase(dlg->dialog);
    dlg_draw_box2(dlg->dialog,
		  0, 0,
		  dlg->height,
		  dlg->width,
		  dialog_attr, border_attr, border2_attr);

    dlg_draw_title(dlg->dialog, dlg->title);
    dlg_draw_helpline(dlg->dialog, FALSE);

    if ((dlg->prompt != 0 && *(dlg->prompt) != 0)
	&& wmove(dlg->dialog, dlg->item_no, 0) != ERR) {
	dlg->caption = dlg_sub_window(dlg->dialog,
				      dlg->height - dlg->item_no - (2 * MARGIN),
				      dlg->width,
				      y + dlg->item_no + (2 * MARGIN),
				      x);
	dlg_attrset(dlg->caption, dialog_attr);
	dlg_print_autowrap(dlg->caption, dlg->prompt, dlg->height, dlg->width);
    }

    mydraw_mixed_box(dlg->dialog,
		     dlg->height - 4,
		     2 + MARGIN,
		     2 + MARGIN,
		     dlg->width - 2 * (2 + MARGIN),
		     dialog_attr,
		     border_attr);

    *began += 1;
}