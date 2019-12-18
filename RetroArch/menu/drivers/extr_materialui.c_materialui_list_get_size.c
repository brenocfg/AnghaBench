#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  num_menu_tabs; } ;
struct TYPE_4__ {TYPE_1__ nav_bar; } ;
typedef  TYPE_2__ materialui_handle_t ;
typedef  enum menu_list_type { ____Placeholder_menu_list_type } menu_list_type ;

/* Variables and functions */
#define  MENU_LIST_PLAIN 129 
#define  MENU_LIST_TABS 128 
 size_t menu_entries_get_stack_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t materialui_list_get_size(void *data, enum menu_list_type type)
{
   materialui_handle_t *mui = (materialui_handle_t*)data;

   switch (type)
   {
      case MENU_LIST_PLAIN:
         return menu_entries_get_stack_size(0);
      case MENU_LIST_TABS:
         if (!mui)
            return 0;
         return (size_t)mui->nav_bar.num_menu_tabs;
      default:
         break;
   }

   return 0;
}