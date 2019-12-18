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
struct TYPE_6__ {int enum_idx; int /*<<< orphan*/  setting; } ;
typedef  TYPE_1__ menu_file_list_cbs_t ;
struct TYPE_7__ {char const* path; char const* label; size_t idx; unsigned int entry_type; int /*<<< orphan*/ * fullpath; int /*<<< orphan*/ * list; } ;
typedef  TYPE_2__ menu_ctx_list_t ;
typedef  int /*<<< orphan*/  file_list_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  file_list_free_actiondata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  file_list_prepend (int /*<<< orphan*/ *,char const*,char const*,unsigned int,size_t,size_t) ; 
 int /*<<< orphan*/  file_list_set_actiondata (int /*<<< orphan*/ *,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_cbs_init (int /*<<< orphan*/ *,TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_driver_list_insert (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_entries_get_last_stack (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_setting_find_enum (int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

void menu_entries_prepend(file_list_t *list,
      const char *path, const char *label,
      enum msg_hash_enums enum_idx,
      unsigned type, size_t directory_ptr, size_t entry_idx)
{
   menu_ctx_list_t list_info;
   size_t idx;
   const char *menu_path           = NULL;
   menu_file_list_cbs_t *cbs       = NULL;
   if (!list || !label)
      return;

   file_list_prepend(list, path, label, type, directory_ptr, entry_idx);

   menu_entries_get_last_stack(&menu_path, NULL, NULL, NULL, NULL);

   idx              = 0;

   list_info.fullpath    = NULL;

   if (!string_is_empty(menu_path))
      list_info.fullpath = strdup(menu_path);
   list_info.list        = list;
   list_info.path        = path;
   list_info.label       = label;
   list_info.idx         = idx;
   list_info.entry_type  = type;

   menu_driver_list_insert(&list_info);

   if (list_info.fullpath)
      free(list_info.fullpath);

   file_list_free_actiondata(list, idx);
   cbs = (menu_file_list_cbs_t*)
      calloc(1, sizeof(menu_file_list_cbs_t));

   if (!cbs)
      return;

   file_list_set_actiondata(list, idx, cbs);

   cbs->enum_idx = enum_idx;
   cbs->setting  = menu_setting_find_enum(cbs->enum_idx);

   menu_cbs_init(list, cbs, path, label, type, idx);
}