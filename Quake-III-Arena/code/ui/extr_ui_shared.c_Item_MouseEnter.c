#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ h; int /*<<< orphan*/  y; } ;
typedef  TYPE_2__ rectDef_t ;
struct TYPE_9__ {int flags; } ;
struct TYPE_11__ {int cvarFlags; scalar_t__ type; TYPE_1__ window; int /*<<< orphan*/  mouseEnter; int /*<<< orphan*/  mouseExitText; int /*<<< orphan*/  mouseEnterText; TYPE_2__ textRect; } ;
typedef  TYPE_3__ itemDef_t ;

/* Variables and functions */
 int CVAR_DISABLE ; 
 int CVAR_ENABLE ; 
 int CVAR_HIDE ; 
 int CVAR_SHOW ; 
 scalar_t__ ITEM_TYPE_LISTBOX ; 
 int /*<<< orphan*/  Item_EnableShowViaCvar (TYPE_3__*,int) ; 
 int /*<<< orphan*/  Item_ListBox_MouseEnter (TYPE_3__*,float,float) ; 
 int /*<<< orphan*/  Item_RunScript (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ Rect_ContainsPoint (TYPE_2__*,float,float) ; 
 int WINDOW_MOUSEOVER ; 
 int WINDOW_MOUSEOVERTEXT ; 

void Item_MouseEnter(itemDef_t *item, float x, float y) {
	rectDef_t r;
	if (item) {
		r = item->textRect;
		r.y -= r.h;
		// in the text rect?

		// items can be enabled and disabled based on cvars
		if (item->cvarFlags & (CVAR_ENABLE | CVAR_DISABLE) && !Item_EnableShowViaCvar(item, CVAR_ENABLE)) {
			return;
		}

		if (item->cvarFlags & (CVAR_SHOW | CVAR_HIDE) && !Item_EnableShowViaCvar(item, CVAR_SHOW)) {
			return;
		}

		if (Rect_ContainsPoint(&r, x, y)) {
			if (!(item->window.flags & WINDOW_MOUSEOVERTEXT)) {
				Item_RunScript(item, item->mouseEnterText);
				item->window.flags |= WINDOW_MOUSEOVERTEXT;
			}
			if (!(item->window.flags & WINDOW_MOUSEOVER)) {
				Item_RunScript(item, item->mouseEnter);
				item->window.flags |= WINDOW_MOUSEOVER;
			}

		} else {
			// not in the text rect
			if (item->window.flags & WINDOW_MOUSEOVERTEXT) {
				// if we were
				Item_RunScript(item, item->mouseExitText);
				item->window.flags &= ~WINDOW_MOUSEOVERTEXT;
			}
			if (!(item->window.flags & WINDOW_MOUSEOVER)) {
				Item_RunScript(item, item->mouseEnter);
				item->window.flags |= WINDOW_MOUSEOVER;
			}

			if (item->type == ITEM_TYPE_LISTBOX) {
				Item_ListBox_MouseEnter(item, x, y);
			}
		}
	}
}