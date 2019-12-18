#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ offset; scalar_t__ max_buttons; scalar_t__ max_items; int selected; TYPE_1__** arrows; } ;
typedef  TYPE_2__ gui_menu ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTON_VISIBLE ; 
 int /*<<< orphan*/  GUI_DrawMenu (TYPE_2__*) ; 
 int GUI_UpdateMenu (TYPE_2__*) ; 

int GUI_RunMenu(gui_menu *menu)
{
  int update = 0;

  /* update menu */
  while (!update)
  {
    GUI_DrawMenu(menu);
    update = GUI_UpdateMenu(menu);

    /* update arrows buttons status (items list) */
    if (menu->arrows[0])
    {
      if (menu->offset > 0)
        menu->arrows[0]->state |= BUTTON_VISIBLE;
      else
        menu->arrows[0]->state &= ~BUTTON_VISIBLE;
    }

    if (menu->arrows[1])
    {
      if ((menu->offset + menu->max_buttons) < menu->max_items)
        menu->arrows[1]->state |= BUTTON_VISIBLE;
      else
        menu->arrows[1]->state &= ~BUTTON_VISIBLE;
    }
  }

  if (update == 2)
    return (-2-menu->offset-menu->selected);
  else if (update == 1)
    return (menu->offset + menu->selected);
  else
    return -1;
 }