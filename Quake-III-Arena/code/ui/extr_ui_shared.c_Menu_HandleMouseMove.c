#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_12__ {int flags; } ;
struct TYPE_14__ {int itemCount; TYPE_4__** items; TYPE_1__ window; } ;
typedef  TYPE_3__ menuDef_t ;
struct TYPE_13__ {int flags; int /*<<< orphan*/  rect; } ;
struct TYPE_15__ {int cvarFlags; scalar_t__ type; TYPE_2__ window; scalar_t__ text; } ;
typedef  TYPE_4__ itemDef_t ;

/* Variables and functions */
 int CVAR_DISABLE ; 
 int CVAR_ENABLE ; 
 int CVAR_HIDE ; 
 int CVAR_SHOW ; 
 scalar_t__ ITEM_TYPE_TEXT ; 
 scalar_t__ IsVisible (int) ; 
 int /*<<< orphan*/ * Item_CorrectedTextRect (TYPE_4__*) ; 
 int /*<<< orphan*/  Item_EnableShowViaCvar (TYPE_4__*,int) ; 
 int /*<<< orphan*/  Item_MouseEnter (TYPE_4__*,float,float) ; 
 int /*<<< orphan*/  Item_MouseLeave (TYPE_4__*) ; 
 scalar_t__ Item_SetFocus (TYPE_4__*,float,float) ; 
 int /*<<< orphan*/  Item_SetMouseOver (TYPE_4__*,scalar_t__) ; 
 scalar_t__ Rect_ContainsPoint (int /*<<< orphan*/ *,float,float) ; 
 int WINDOW_FORCED ; 
 int WINDOW_MOUSEOVER ; 
 int WINDOW_VISIBLE ; 
 scalar_t__ g_editingField ; 
 scalar_t__ g_waitingForKey ; 
 scalar_t__ itemCapture ; 
 scalar_t__ qfalse ; 

void Menu_HandleMouseMove(menuDef_t *menu, float x, float y) {
  int i, pass;
  qboolean focusSet = qfalse;

  itemDef_t *overItem;
  if (menu == NULL) {
    return;
  }

  if (!(menu->window.flags & (WINDOW_VISIBLE | WINDOW_FORCED))) {
    return;
  }

	if (itemCapture) {
		//Item_MouseMove(itemCapture, x, y);
		return;
	}

	if (g_waitingForKey || g_editingField) {
		return;
	}

  // FIXME: this is the whole issue of focus vs. mouse over.. 
  // need a better overall solution as i don't like going through everything twice
  for (pass = 0; pass < 2; pass++) {
    for (i = 0; i < menu->itemCount; i++) {
      // turn off focus each item
      // menu->items[i].window.flags &= ~WINDOW_HASFOCUS;

      if (!(menu->items[i]->window.flags & (WINDOW_VISIBLE | WINDOW_FORCED))) {
        continue;
      }

			// items can be enabled and disabled based on cvars
			if (menu->items[i]->cvarFlags & (CVAR_ENABLE | CVAR_DISABLE) && !Item_EnableShowViaCvar(menu->items[i], CVAR_ENABLE)) {
				continue;
			}

			if (menu->items[i]->cvarFlags & (CVAR_SHOW | CVAR_HIDE) && !Item_EnableShowViaCvar(menu->items[i], CVAR_SHOW)) {
				continue;
			}



      if (Rect_ContainsPoint(&menu->items[i]->window.rect, x, y)) {
				if (pass == 1) {
					overItem = menu->items[i];
					if (overItem->type == ITEM_TYPE_TEXT && overItem->text) {
						if (!Rect_ContainsPoint(Item_CorrectedTextRect(overItem), x, y)) {
							continue;
						}
					}
					// if we are over an item
					if (IsVisible(overItem->window.flags)) {
						// different one
						Item_MouseEnter(overItem, x, y);
						// Item_SetMouseOver(overItem, qtrue);

						// if item is not a decoration see if it can take focus
						if (!focusSet) {
							focusSet = Item_SetFocus(overItem, x, y);
						}
					}
				}
      } else if (menu->items[i]->window.flags & WINDOW_MOUSEOVER) {
          Item_MouseLeave(menu->items[i]);
          Item_SetMouseOver(menu->items[i], qfalse);
      }
    }
  }

}