#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; char* prefix; char* item; char* suffix; int retval; } ;
typedef  TYPE_1__ UI_tMenuItem ;

/* Variables and functions */
 int /*<<< orphan*/  Box (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ClearScreen () ; 
 int /*<<< orphan*/  FALSE ; 
 int Select (int,int,char const**,char const**,char const**,char const**,int*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TitleScreen (char const*) ; 
 int UI_ITEM_CHECK ; 
 int UI_ITEM_CHECKED ; 
 int UI_ITEM_END ; 
 int UI_ITEM_HIDDEN ; 
 int UI_ITEM_TIP ; 
 int UI_ITEM_TYPE ; 
 int UI_SELECT_DRAG ; 
 int UI_SELECT_POPUP ; 
 int strlen (char const*) ; 

__attribute__((used)) static int BasicUISelect(const char *title, int flags, int default_item, const UI_tMenuItem *menu, int *seltype)
{
	int nitems;
	int index;
	const UI_tMenuItem *pmenu;
	static const char *prefix[100];
	static const char *item[100];
	static const char *suffix[100];
	static const char *tip[100];
	static int nonselectable[100];
	int w;
	int x1, y1, x2, y2;

	nitems = 0;
	index = 0;
	for (pmenu = menu; pmenu->flags != UI_ITEM_END; pmenu++) {
		if (pmenu->flags != UI_ITEM_HIDDEN) {
			prefix[nitems] = pmenu->prefix;
			item[nitems] = pmenu->item;
			if (pmenu->flags & UI_ITEM_TIP) {
				suffix[nitems] = NULL;
				tip[nitems] = pmenu->suffix;
			}
			else {
				if ((pmenu->flags & UI_ITEM_TYPE) == UI_ITEM_CHECK) {
					if (pmenu->flags & UI_ITEM_CHECKED)
						suffix[nitems] = "Yes";
					else
						suffix[nitems] = "No ";
				}
				else
					suffix[nitems] = pmenu->suffix;
				tip[nitems] = NULL;
			}
			nonselectable[nitems] = (pmenu->retval < 0);
			if (pmenu->retval == default_item)
				index = nitems;
			nitems++;
		}
	}
	if (nitems == 0)
		return -1; /* cancel immediately */

	if (flags & UI_SELECT_POPUP) {
		int i;
		w = 0;
		for (i = 0; i < nitems; i++) {
			int ws = strlen(item[i]);
			if (prefix[i] != NULL)
				ws += strlen(prefix[i]);
			if (suffix[i] != NULL)
				ws += strlen(suffix[i]);
			if (ws > w)
				w = ws;
		}
		if (w > 38)
			w = 38;

		x1 = (40 - w) / 2 - 1;
		x2 = x1 + w + 1;
		y1 = (24 - nitems) / 2 - 1;
		y2 = y1 + nitems + 1;
	}
	else {
		ClearScreen();
		TitleScreen(title);
		w = 38;
		x1 = 0;
		y1 = 1;
		x2 = 39;
		y2 = 23;
	}

	if (y1 < 0)
		y1 = 0;
	if (y2 > 23)
		y2 = 23;

	Box(0x9a, 0x94, x1, y1, x2, y2);
	index = Select(index, nitems, item, prefix, suffix, tip, nonselectable,
	                y2 - y1 - 1, 1, x1 + 1, y1 + 1, w,
	                (flags & UI_SELECT_DRAG) ? TRUE : FALSE, NULL, seltype);
	if (index < 0)
		return index;
	for (pmenu = menu; pmenu->flags != UI_ITEM_END; pmenu++) {
		if (pmenu->flags != UI_ITEM_HIDDEN) {
			if (index == 0)
				return pmenu->retval;
			index--;
		}
	}
	/* shouldn't happen */
	return -1;
}