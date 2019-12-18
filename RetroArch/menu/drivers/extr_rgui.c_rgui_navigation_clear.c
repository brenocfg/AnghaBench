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
struct TYPE_2__ {scalar_t__ scroll_y; } ;
typedef  TYPE_1__ rgui_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_START ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static void rgui_navigation_clear(void *data, bool pending_push)
{
   size_t start;
   rgui_t           *rgui = (rgui_t*)data;
   if (!rgui)
      return;

   start = 0;
   menu_entries_ctl(MENU_ENTRIES_CTL_SET_START, &start);
   rgui->scroll_y = 0;
}