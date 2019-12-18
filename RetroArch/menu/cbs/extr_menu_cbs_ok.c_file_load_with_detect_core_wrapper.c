#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* scratch2_buf; char const* scratch_buf; char* detect_content_path; int /*<<< orphan*/  deferred_path; } ;
typedef  TYPE_1__ menu_handle_t ;
struct TYPE_8__ {char* dir; char const* path; char const* menu_label; int len; int /*<<< orphan*/  s; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ menu_content_ctx_defer_info_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;
typedef  int /*<<< orphan*/  core_info_list_t ;
struct TYPE_9__ {int /*<<< orphan*/ * environ_get; int /*<<< orphan*/ * args; int /*<<< orphan*/ * argv; int /*<<< orphan*/  argc; } ;
typedef  TYPE_3__ content_ctx_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_OK_DL_DEFERRED_CORE_LIST ; 
 int /*<<< orphan*/  ACTION_OK_DL_DEFERRED_CORE_LIST_SET ; 
 int /*<<< orphan*/  CORE_TYPE_PLAIN ; 
 int MENU_ENUM_LABEL_COLLECTION ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_ARCHIVE_OPEN ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_ARCHIVE_OPEN_DETECT_CORE ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  content_add_to_playlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_info_get_list (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char*,char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int generic_action_ok_displaylist_push (char const*,int /*<<< orphan*/ *,char const*,unsigned int,size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int menu_cbs_exit () ; 
 scalar_t__ menu_content_find_first_core (TYPE_2__*,int,char*,int) ; 
 TYPE_1__* menu_driver_get_ptr () ; 
 int /*<<< orphan*/  menu_entries_get_last_stack (char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  task_push_load_content_with_new_core_from_menu (char*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int file_load_with_detect_core_wrapper(
      enum msg_hash_enums enum_label_idx,
      size_t idx, size_t entry_idx,
      const char *path, const char *label,
      unsigned type, bool is_carchive)
{
   menu_content_ctx_defer_info_t def_info;
   int ret                             = 0;
   char *new_core_path                 = NULL;
   const char *menu_path               = NULL;
   const char *menu_label              = NULL;
   core_info_list_t *list              = NULL;
   menu_handle_t *menu                 = menu_driver_get_ptr();

   if (!menu)
      return menu_cbs_exit();

   {
      char *menu_path_new = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
      new_core_path       = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
      new_core_path[0]    = menu_path_new[0] = '\0';

      menu_entries_get_last_stack(&menu_path, &menu_label, NULL, NULL, NULL);

      if (!string_is_empty(menu_path))
         strlcpy(menu_path_new, menu_path, PATH_MAX_LENGTH * sizeof(char));

      if (string_is_equal(menu_label,
               msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_ARCHIVE_OPEN_DETECT_CORE)))
         fill_pathname_join(menu_path_new, menu->scratch2_buf, menu->scratch_buf,
               PATH_MAX_LENGTH * sizeof(char));
      else if (string_is_equal(menu_label,
               msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_ARCHIVE_OPEN)))
         fill_pathname_join(menu_path_new, menu->scratch2_buf, menu->scratch_buf,
               PATH_MAX_LENGTH * sizeof(char));

      core_info_get_list(&list);

      def_info.data       = list;
      def_info.dir        = menu_path_new;
      def_info.path       = path;
      def_info.menu_label = menu_label;
      def_info.s          = menu->deferred_path;
      def_info.len        = sizeof(menu->deferred_path);

      if (menu_content_find_first_core(&def_info, false, new_core_path,
               PATH_MAX_LENGTH * sizeof(char)))
         ret = -1;

      if (     !is_carchive && !string_is_empty(path)
            && !string_is_empty(menu_path_new))
         fill_pathname_join(menu->detect_content_path,
               menu_path_new, path,
               sizeof(menu->detect_content_path));

      free(menu_path_new);

      if (enum_label_idx == MENU_ENUM_LABEL_COLLECTION)
      {
         free(new_core_path);
         return generic_action_ok_displaylist_push(path, NULL,
               NULL, 0, idx, entry_idx, ACTION_OK_DL_DEFERRED_CORE_LIST_SET);
      }

      switch (ret)
      {
         case -1:
            {
               content_ctx_info_t content_info;

               content_info.argc        = 0;
               content_info.argv        = NULL;
               content_info.args        = NULL;
               content_info.environ_get = NULL;

               if (!task_push_load_content_with_new_core_from_menu(
                        new_core_path, def_info.s,
                        &content_info,
                        CORE_TYPE_PLAIN,
                        NULL, NULL))
               {
                  free(new_core_path);
                  return -1;
               }
               content_add_to_playlist(def_info.s);

               ret = 0;
               break;
            }
         case 0:
            ret = generic_action_ok_displaylist_push(path, NULL, label, type,
                  idx, entry_idx, ACTION_OK_DL_DEFERRED_CORE_LIST);
            break;
         default:
            break;
      }
   }

   free(new_core_path);
   return ret;
}