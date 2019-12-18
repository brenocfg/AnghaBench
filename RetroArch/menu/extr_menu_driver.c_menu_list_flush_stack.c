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
typedef  int /*<<< orphan*/  menu_list_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_REFRESH ; 
 int /*<<< orphan*/  file_list_get_last (int /*<<< orphan*/ *,char const**,char const**,unsigned int*,size_t*) ; 
 size_t menu_driver_selection_ptr ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ menu_list_flush_stack_type (char const*,char const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * menu_list_get (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  menu_list_pop_stack (int /*<<< orphan*/ *,size_t,size_t*,int) ; 

__attribute__((used)) static void menu_list_flush_stack(menu_list_t *list,
      size_t idx, const char *needle, unsigned final_type)
{
   bool refresh           = false;
   const char *path       = NULL;
   const char *label      = NULL;
   unsigned type          = 0;
   size_t entry_idx       = 0;
   file_list_t *menu_list = menu_list_get(list, (unsigned)idx);

   menu_entries_ctl(MENU_ENTRIES_CTL_SET_REFRESH, &refresh);
   file_list_get_last(menu_list,
         &path, &label, &type, &entry_idx);

   while (menu_list_flush_stack_type(
            needle, label, type, final_type) != 0)
   {
      size_t new_selection_ptr = menu_driver_selection_ptr;

      if (!menu_list_pop_stack(list, idx, &new_selection_ptr, 1))
         break;

      menu_driver_selection_ptr = new_selection_ptr;

      menu_list = menu_list_get(list, (unsigned)idx);

      file_list_get_last(menu_list,
            &path, &label, &type, &entry_idx);
   }
}