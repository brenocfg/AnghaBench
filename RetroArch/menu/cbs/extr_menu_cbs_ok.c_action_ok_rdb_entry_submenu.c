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
union string_list_elem_attr {scalar_t__ i; } ;
struct string_list {TYPE_1__* elems; } ;
typedef  int /*<<< orphan*/  new_path ;
typedef  int /*<<< orphan*/  new_label ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_OK_DL_RDB_ENTRY_SUBMENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_CURSOR_MANAGER_LIST ; 
 int PATH_MAX_LENGTH ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fill_pathname_join_delim (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int generic_action_ok_displaylist_push (char*,int /*<<< orphan*/ *,char*,unsigned int,size_t,size_t,int /*<<< orphan*/ ) ; 
 int menu_cbs_exit () ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ,union string_list_elem_attr) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 int /*<<< orphan*/  string_list_join_concat (char*,int,struct string_list*,char*) ; 
 struct string_list* string_list_new () ; 
 struct string_list* string_split (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int action_ok_rdb_entry_submenu(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   union string_list_elem_attr attr;
   char new_label[PATH_MAX_LENGTH];
   char new_path[PATH_MAX_LENGTH];
   int ret                         = -1;
   char *rdb                       = NULL;
   int len                         = 0;
   struct string_list *str_list    = NULL;
   struct string_list *str_list2   = NULL;

   if (!label)
      return menu_cbs_exit();

   new_label[0] = new_path[0]      = '\0';

   str_list = string_split(label, "|");

   if (!str_list)
      goto end;

   str_list2 = string_list_new();
   if (!str_list2)
      goto end;

   /* element 0 : label
    * element 1 : value
    * element 2 : database path
    */

   attr.i = 0;

   len += strlen(str_list->elems[1].data) + 1;
   string_list_append(str_list2, str_list->elems[1].data, attr);

   len += strlen(str_list->elems[2].data) + 1;
   string_list_append(str_list2, str_list->elems[2].data, attr);

   rdb = (char*)calloc(len, sizeof(char));

   if (!rdb)
      goto end;

   string_list_join_concat(rdb, len, str_list2, "|");
   strlcpy(new_path, rdb, sizeof(new_path));

   fill_pathname_join_delim(new_label,
         msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_CURSOR_MANAGER_LIST),
         str_list->elems[0].data, '_',
         sizeof(new_label));

   ret = generic_action_ok_displaylist_push(new_path, NULL,
         new_label, type, idx, entry_idx,
         ACTION_OK_DL_RDB_ENTRY_SUBMENU);

end:
   if (rdb)
      free(rdb);
   if (str_list)
      string_list_free(str_list);
   if (str_list2)
      string_list_free(str_list2);

   return ret;
}