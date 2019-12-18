#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int itemCount; TYPE_3__** items; } ;
typedef  TYPE_2__ menuDef_t ;
struct TYPE_6__ {int flags; } ;
struct TYPE_8__ {TYPE_1__ window; } ;
typedef  TYPE_3__ itemDef_t ;

/* Variables and functions */
 int WINDOW_HASFOCUS ; 

itemDef_t *Menu_GetFocusedItem(menuDef_t *menu) {
  int i;
  if (menu) {
    for (i = 0; i < menu->itemCount; i++) {
      if (menu->items[i]->window.flags & WINDOW_HASFOCUS) {
        return menu->items[i];
      }
    }
  }
  return NULL;
}