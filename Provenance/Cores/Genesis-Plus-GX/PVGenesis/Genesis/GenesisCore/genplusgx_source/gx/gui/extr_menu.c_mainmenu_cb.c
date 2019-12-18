#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int selected; TYPE_1__* items; } ;
typedef  TYPE_2__ gui_menu ;
struct TYPE_4__ {int h; scalar_t__ y; scalar_t__ x; } ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 int AR_SWITCH_ON ; 
 int AR_SWITCH_TRAINER ; 
 scalar_t__ DARK_GREY ; 
 int /*<<< orphan*/  FONT_writeCenter (char*,int,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int areplay_get_status () ; 
 TYPE_2__ menu_main ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void mainmenu_cb(void)
{
  char temp[4];
  gui_menu *m = &menu_main;
  int status = areplay_get_status();

  /* Action Replay Switch current status */
  if (status == AR_SWITCH_TRAINER) strcpy(temp,"TM");
  else if (status == AR_SWITCH_ON) strcpy(temp,"ON");
  else strcpy(temp,"OFF");

  /* Display informations */
  if (m->selected == 6)
  {
    FONT_writeCenter("Action\nReplay", 14, m->items[6].x, m->items[6].x + 54, m->items[6].y + (m->items[6].h - 28)/2 + 14, (GXColor)DARK_GREY);
    FONT_writeCenter(temp, 11, m->items[6].x + 56 + 3, m->items[6].x + 78 + 2, m->items[6].y + (m->items[6].h - 11)/2 + 11, (GXColor)DARK_GREY);
  }
  else
  {
    FONT_writeCenter("Action\nReplay", 12, m->items[6].x + 4, m->items[6].x + 54, m->items[6].y + (m->items[6].h - 24)/2 + 12, (GXColor)DARK_GREY);
    FONT_writeCenter(temp, 10, m->items[6].x + 56, m->items[6].x + 78, m->items[6].y + (m->items[6].h - 10)/2 + 10, (GXColor)DARK_GREY);
  }
}