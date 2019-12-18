#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  setting; int /*<<< orphan*/  enum_idx; } ;
typedef  TYPE_1__ menu_file_list_cbs_t ;
struct TYPE_13__ {char const* path; char const* label; size_t idx; unsigned int entry_type; int /*<<< orphan*/ * fullpath; TYPE_3__* list; } ;
typedef  TYPE_2__ menu_ctx_list_t ;
struct TYPE_14__ {int size; } ;
typedef  TYPE_3__ file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_UNKNOWN ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  file_list_append (TYPE_3__*,char const*,char const*,unsigned int,size_t,size_t) ; 
 int /*<<< orphan*/  file_list_free_actiondata (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  file_list_set_actiondata (TYPE_3__*,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_cbs_init (TYPE_3__*,TYPE_1__*,char const*,char const*,unsigned int,size_t) ; 
 int /*<<< orphan*/  menu_driver_list_insert (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_entries_get_last_stack (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_setting_find (char const*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

void menu_entries_append(file_list_t *list, const char *path, const char *label,
      unsigned type, size_t directory_ptr, size_t entry_idx)
{
   menu_ctx_list_t list_info;
   size_t idx;
   const char *menu_path           = NULL;
   menu_file_list_cbs_t *cbs       = NULL;
   if (!list || !label)
      return;

   file_list_append(list, path, label, type, directory_ptr, entry_idx);

   menu_entries_get_last_stack(&menu_path, NULL, NULL, NULL, NULL);

   idx                = list->size - 1;

   list_info.list     = list;
   list_info.path     = path;
   list_info.fullpath = NULL;

   if (!string_is_empty(menu_path))
      list_info.fullpath = strdup(menu_path);

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

   cbs->enum_idx = MSG_UNKNOWN;
   cbs->setting  = menu_setting_find(label);

   menu_cbs_init(list, cbs, path, label, type, idx);
}