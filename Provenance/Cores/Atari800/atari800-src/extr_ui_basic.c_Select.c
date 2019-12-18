#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int y; int x; } ;

/* Variables and functions */
 int /*<<< orphan*/  CenterPrint (int,int,char const*,int) ; 
 int /*<<< orphan*/  ClearRectangle (int,int,int,int,int) ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int GetKeyPress () ; 
 int /*<<< orphan*/  Print (int,int,char*,int,int,int) ; 
 int UI_USER_DELETE ; 
 int UI_USER_DRAG_DOWN ; 
 int UI_USER_DRAG_UP ; 
 int UI_USER_SELECT ; 
 int UI_USER_TOGGLE ; 
 TYPE_1__ UI_mouse_click ; 
 int /*<<< orphan*/  Util_chrieq (char,char const) ; 
 char* Util_stpcpy (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strlen (char const*) ; 

__attribute__((used)) static int Select(int default_item, int nitems, const char *item[],
                  const char *prefix[], const char *suffix[],
                  const char *tip[], const int nonselectable[],
                  int nrows, int ncolumns, int xoffset, int yoffset,
                  int itemwidth, int drag, const char *global_tip,
                  int *seltype)
{
	int offset = 0;
	int index = default_item;
	int localseltype;

	if (seltype == NULL)
		seltype = &localseltype;

	for (;;) {
		int col;
		int row;
		int i;
		const char *message = global_tip;

		while (index < offset)
			offset -= nrows;
		while (index >= offset + nrows * ncolumns)
			offset += nrows;

		ClearRectangle(0x94, xoffset, yoffset, xoffset + ncolumns * (itemwidth + 1) - 2, yoffset + nrows - 1);
		col = 0;
		row = 0;
		for (i = offset; i < nitems; i++) {
			char szbuf[40 + FILENAME_MAX]; /* allow for prefix and suffix */
			char *p = szbuf;
			if (prefix != NULL && prefix[i] != NULL)
				p = Util_stpcpy(szbuf, prefix[i]);
			p = Util_stpcpy(p, item[i]);
			if (suffix != NULL && suffix[i] != NULL) {
				char *q = szbuf + itemwidth - strlen(suffix[i]);
				while (p < q)
					*p++ = ' ';
				strcpy(p, suffix[i]);
			}
			else {
				while (p < szbuf + itemwidth)
					*p++ = ' ';
				*p = '\0';
			}
			if (i == index)
				Print(0x94, 0x9a, szbuf, xoffset + col * (itemwidth + 1), yoffset + row, itemwidth);
			else
				Print(0x9a, 0x94, szbuf, xoffset + col * (itemwidth + 1), yoffset + row, itemwidth);
			if (++row >= nrows) {
				if (++col >= ncolumns)
					break;
				row = 0;
			}
		}
		if (tip != NULL && tip[index] != NULL)
			message = tip[index];
		else if (itemwidth < 38 && (int) strlen(item[index]) > itemwidth)
			/* the selected item was shortened */
			message = item[index];
		if (message != NULL)
			CenterPrint(0x94, 0x9a, message, 22);

		for (;;) {
			int ascii;
			int tmp_index;
			ascii = GetKeyPress();
			switch (ascii) {
			case 0x1c:				/* Up */
				if (drag) {
					*seltype = UI_USER_DRAG_UP;
					return index;
				}
				tmp_index = index;
				do
					tmp_index--;
				while (tmp_index >= 0 && nonselectable != NULL && nonselectable[tmp_index]);
				if (tmp_index >= 0) {
					index = tmp_index;
					break;
				}
				continue;
			case 0x1d:				/* Down */
				if (drag) {
					*seltype = UI_USER_DRAG_DOWN;
					return index;
				}
				tmp_index = index;
				do
					tmp_index++;
				while (tmp_index < nitems && nonselectable != NULL && nonselectable[tmp_index]);
				if (tmp_index < nitems) {
					index = tmp_index;
					break;
				}
				continue;
			case 0x1e:				/* Left */
				if (drag)
					continue;		/* cannot drag left */
				index = (index > nrows) ? index - nrows : 0;
				break;
			case 0x1f:				/* Right */
				if (drag)
					continue;		/* cannot drag right */
				index = (index + nrows < nitems) ? index + nrows : nitems - 1;
				break;
			case 0x7f:				/* Tab (for exchanging disk directories) */
				return -2;			/* GOLDA CHANGED */
			case 0x20:				/* Space */
				*seltype = UI_USER_TOGGLE;
				return index;
			case 0x7e:				/* Backspace */
				*seltype = UI_USER_DELETE;
				return index;
			case 0x9b:				/* Return=Select */
				*seltype = UI_USER_SELECT;
				return index;
#ifdef DIRECTX
			case 0xAA:              /* Mouse click */
			
			/* mouse click location, adjusted by context 
			   this is all we need for one column */
			tmp_index = UI_mouse_click.y - yoffset + 2;
					  
			/* handle two column mode scenarios */
			if (ncolumns == 2) {
				/* special case - do nothing if user clicks empty 
			       bottom cell in column 1 in two column mode.   */	
				if (UI_mouse_click.x == 1 && UI_mouse_click.y == 20) {
					UI_mouse_click.x = UI_mouse_click.y = -1;
					break;
				} 
				/* handle two column, multi-page scenarios */
				else if (UI_mouse_click.x == 1) 
					tmp_index += offset;
				else if (UI_mouse_click.x == 2)
					tmp_index += offset + 20;
			}

			/* if cell is a valid one, update the index */
			if (tmp_index > -1 && tmp_index < nitems)
				index = tmp_index;
			else 
				/* otherwise, invalid item, so do nothing */
				UI_mouse_click.x = UI_mouse_click.y = -1;
				
			break;
#endif 
			case 0x1b:				/* Esc=Cancel */
				return -1;
			default:
				if (drag || ascii <= 0x20 || ascii >= 0x7f)
					continue;
				tmp_index = index; /* old index */
				do {
					if (++index >= nitems)
						index = 0;
				} while (index != tmp_index && !Util_chrieq((char) ascii, item[index][0]));
				break;
			}
			break;
		}
		if (message != NULL)
			ClearRectangle(0x94, 1, 22, 38, 22);
	}
}