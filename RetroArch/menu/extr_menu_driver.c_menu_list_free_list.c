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
struct TYPE_6__ {unsigned int idx; unsigned int list_size; TYPE_2__* list; } ;
typedef  TYPE_1__ menu_ctx_list_t ;
struct TYPE_7__ {unsigned int size; } ;
typedef  TYPE_2__ file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_MENU_CTL_LIST_FREE ; 
 int /*<<< orphan*/  file_list_free (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void menu_list_free_list(file_list_t *list)
{
   unsigned i;

   for (i = 0; i < list->size; i++)
   {
      menu_ctx_list_t list_info;

      list_info.list      = list;
      list_info.idx       = i;
      list_info.list_size = list->size;

      menu_driver_ctl(RARCH_MENU_CTL_LIST_FREE, &list_info);
   }

   file_list_free(list);
}