#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_START ; 
 int /*<<< orphan*/  MUI_ANIM_DURATION_SCROLL_RESET ; 
 int /*<<< orphan*/  materialui_animate_scroll (int /*<<< orphan*/ *,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static void materialui_navigation_clear(void *data, bool pending_push)
{
   size_t i                 = 0;
   materialui_handle_t *mui = (materialui_handle_t*)data;
   if (!mui)
      return;

   menu_entries_ctl(MENU_ENTRIES_CTL_SET_START, &i);

   materialui_animate_scroll(
         mui,
         0.0f,
         MUI_ANIM_DURATION_SCROLL_RESET);
}