#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  menu_list_t ;
struct TYPE_8__ {scalar_t__ idx; scalar_t__ list_size; TYPE_2__* list; scalar_t__ action; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ menu_ctx_list_t ;
struct TYPE_9__ {scalar_t__ size; } ;
typedef  TYPE_2__ file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_REFRESH ; 
 int /*<<< orphan*/  MENU_LIST_PLAIN ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_LIST_FREE ; 
 int /*<<< orphan*/  file_list_pop (TYPE_2__*,size_t*) ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  menu_driver_list_cache (TYPE_1__*) ; 
 int /*<<< orphan*/  menu_driver_list_set_selection (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 
 TYPE_2__* menu_list_get (int /*<<< orphan*/ *,unsigned int) ; 
 int menu_list_get_stack_size (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static bool menu_list_pop_stack(menu_list_t *list,
      size_t idx, size_t *directory_ptr, bool animate)
{
   menu_ctx_list_t list_info;
   bool refresh           = false;
   file_list_t *menu_list = menu_list_get(list, (unsigned)idx);

   if (menu_list_get_stack_size(list, idx) <= 1)
      return false;

   list_info.type   = MENU_LIST_PLAIN;
   list_info.action = 0;

   if (animate)
      menu_driver_list_cache(&list_info);

   if (menu_list->size != 0)
   {
      menu_ctx_list_t list_info;

      list_info.list      = menu_list;
      list_info.idx       = menu_list->size - 1;
      list_info.list_size = menu_list->size - 1;

      menu_driver_ctl(RARCH_MENU_CTL_LIST_FREE, &list_info);
   }

   file_list_pop(menu_list, directory_ptr);
   menu_driver_list_set_selection(menu_list);
   if (animate)
      menu_entries_ctl(MENU_ENTRIES_CTL_SET_REFRESH, &refresh);

   return true;
}