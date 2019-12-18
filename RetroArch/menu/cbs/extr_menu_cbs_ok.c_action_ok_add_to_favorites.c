#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
union string_list_elem_attr {scalar_t__ i; } ;
struct string_list {int dummy; } ;
struct retro_system_info {char const* library_name; } ;
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_11__ {int /*<<< orphan*/  rpl_entry_selection_ptr; } ;
typedef  TYPE_3__ menu_handle_t ;
struct TYPE_9__ {char const* label; } ;
struct TYPE_12__ {TYPE_1__ name; } ;
typedef  TYPE_4__ global_t ;
typedef  int /*<<< orphan*/  core_path ;
typedef  int /*<<< orphan*/  core_name ;
struct TYPE_13__ {char* path; TYPE_2__* inf; } ;
typedef  TYPE_5__ core_info_ctx_find_t ;
typedef  int /*<<< orphan*/  content_label ;
struct TYPE_10__ {char const* display_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_ADD_TO_FAVORITES ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ core_info_find (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  fill_short_pathname_representation (char*,char const*,int) ; 
 TYPE_4__* global_get_ptr () ; 
 int menu_cbs_exit () ; 
 TYPE_3__* menu_driver_get_ptr () ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  playlist_get_crc32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  playlist_get_db_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ playlist_index_is_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char*) ; 
 struct retro_system_info* runloop_get_libretro_system_info () ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*,union string_list_elem_attr) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_list_new () ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int action_ok_add_to_favorites(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   const char *content_path = path_get(RARCH_PATH_CONTENT);
   int ret = 0;

   /* Error checking
    * > If content path is empty, cannot do anything... */
   if (!string_is_empty(content_path))
   {
      global_t *global                 = global_get_ptr();
      struct retro_system_info *system = runloop_get_libretro_system_info();
      struct string_list *str_list     = NULL;
      const char *crc32                = NULL;
      const char *db_name              = NULL;

      union string_list_elem_attr attr;
      char content_label[PATH_MAX_LENGTH];
      char core_path[PATH_MAX_LENGTH];
      char core_name[PATH_MAX_LENGTH];

      content_label[0] = '\0';
      core_path[0] = '\0';
      core_name[0] = '\0';

      /* Create string list container for playlist parameters */
      attr.i = 0;
      str_list = string_list_new();
      if (!str_list)
         return 0;

      /* Determine playlist parameters */

      /* > content_label */
      if (global)
         if (!string_is_empty(global->name.label))
            strlcpy(content_label, global->name.label, sizeof(content_label));

      if (string_is_empty(content_label)) /* Label is empty - use file name instead */
         fill_short_pathname_representation(content_label, content_path, sizeof(content_label));

      /* > core_path + core_name */
      if (system)
      {
         if (!string_is_empty(path_get(RARCH_PATH_CORE)))
         {
            core_info_ctx_find_t core_info;

            /* >> core_path */
            strlcpy(core_path, path_get(RARCH_PATH_CORE), sizeof(core_path));

            /* >> core_name
             * (always use display name, if available) */
            core_info.inf  = NULL;
            core_info.path = core_path;

            if (core_info_find(&core_info, core_path))
               if (!string_is_empty(core_info.inf->display_name))
                  strlcpy(core_name, core_info.inf->display_name, sizeof(core_name));
         }

         /* >> core_name (continued) */
         if (string_is_empty(core_name) && !string_is_empty(system->library_name))
            strlcpy(core_name, system->library_name, sizeof(core_name));
      }

      if (string_is_empty(core_path) || string_is_empty(core_name))
      {
         strlcpy(core_path, "DETECT", sizeof(core_path));
         strlcpy(core_name, "DETECT", sizeof(core_name));
      }

      /* > crc32 + db_name */
      {
         menu_handle_t *menu                 = menu_driver_get_ptr();
         if (menu)
         {
            playlist_t *playlist_curr = playlist_get_cached();

            if (playlist_index_is_valid(playlist_curr, menu->rpl_entry_selection_ptr, content_path, core_path))
            {
               playlist_get_crc32(playlist_curr, menu->rpl_entry_selection_ptr, &crc32);
               playlist_get_db_name(playlist_curr, menu->rpl_entry_selection_ptr, &db_name);
            }
         }
      }

      /* Copy playlist parameters into string list
       *   [0]: content_path
       *   [1]: content_label
       *   [2]: core_path
       *   [3]: core_name
       *   [4]: crc32
       *   [5]: db_name */
      string_list_append(str_list, content_path, attr);
      string_list_append(str_list, content_label, attr);
      string_list_append(str_list, core_path, attr);
      string_list_append(str_list, core_name, attr);
      string_list_append(str_list, !string_is_empty(crc32) ? crc32 : "", attr);
      string_list_append(str_list, !string_is_empty(db_name) ? db_name : "", attr);

      /* Trigger 'ADD_TO_FAVORITES' event */
      if (!command_event(CMD_EVENT_ADD_TO_FAVORITES, (void*)str_list))
         ret = menu_cbs_exit();

      /* Clean up */
      string_list_free(str_list);
      str_list = NULL;
   }

   return ret;
}