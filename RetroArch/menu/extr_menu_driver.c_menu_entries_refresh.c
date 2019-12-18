#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; } ;
typedef  TYPE_1__ file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_NAVIGATION_CTL_CLEAR ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  menu_driver_navigation_set (int) ; 
 size_t menu_driver_selection_ptr ; 
 int /*<<< orphan*/  menu_entries_build_scroll_indices (TYPE_1__*) ; 
 size_t menu_entries_get_size () ; 

__attribute__((used)) static bool menu_entries_refresh(file_list_t *list)
{
   size_t list_size;
   size_t selection  = menu_driver_selection_ptr;

   if (list->size)
      menu_entries_build_scroll_indices(list);

   list_size         = menu_entries_get_size();

   if ((selection >= list_size) && list_size)
   {
      size_t idx                = list_size - 1;
      menu_driver_selection_ptr = idx;
      menu_driver_navigation_set(true);
   }
   else if (!list_size)
   {
      bool pending_push = true;
      menu_driver_ctl(MENU_NAVIGATION_CTL_CLEAR, &pending_push);
   }

   return true;
}