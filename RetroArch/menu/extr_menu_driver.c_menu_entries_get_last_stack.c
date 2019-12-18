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
struct TYPE_7__ {int enum_idx; } ;
typedef  TYPE_2__ menu_file_list_cbs_t ;
struct TYPE_8__ {int size; TYPE_1__* list; } ;
typedef  TYPE_3__ file_list_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;
struct TYPE_6__ {scalar_t__ actiondata; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_list_get_last (TYPE_3__*,char const**,char const**,unsigned int*,size_t*) ; 
 int /*<<< orphan*/  menu_entries_list ; 
 TYPE_3__* menu_list_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void menu_entries_get_last_stack(const char **path, const char **label,
      unsigned *file_type, enum msg_hash_enums *enum_idx, size_t *entry_idx)
{
   file_list_t *list              = NULL;
   if (!menu_entries_list)
      return;

   list = menu_list_get(menu_entries_list, 0);

   file_list_get_last(list,
         path, label, file_type, entry_idx);

   if (enum_idx)
   {
      menu_file_list_cbs_t *cbs  = (menu_file_list_cbs_t*)
         list->list[list->size - 1].actiondata;

      if (cbs)
         *enum_idx = cbs->enum_idx;
   }
}