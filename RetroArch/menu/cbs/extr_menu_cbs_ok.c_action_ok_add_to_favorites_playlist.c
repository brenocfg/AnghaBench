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
union string_list_elem_attr {scalar_t__ i; } ;
struct string_list {int dummy; } ;
struct playlist_entry {char* path; char* label; char* core_path; char* core_name; char* crc32; char* db_name; } ;
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_7__ {int /*<<< orphan*/  rpl_entry_selection_ptr; } ;
typedef  TYPE_2__ menu_handle_t ;
typedef  int /*<<< orphan*/  fallback_content_label ;
struct TYPE_8__ {char* path; TYPE_1__* inf; } ;
typedef  TYPE_3__ core_info_ctx_find_t ;
typedef  int /*<<< orphan*/  core_display_name ;
struct TYPE_6__ {char* display_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_ADD_TO_FAVORITES ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ core_info_find (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  fill_short_pathname_representation (char*,char*,int) ; 
 int menu_cbs_exit () ; 
 TYPE_2__* menu_driver_get_ptr () ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  playlist_get_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct playlist_entry const**) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char*,union string_list_elem_attr) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_list_new () ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int action_ok_add_to_favorites_playlist(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   playlist_t *playlist_curr           = playlist_get_cached();
   const struct playlist_entry *entry  = NULL;
   menu_handle_t *menu                 = menu_driver_get_ptr();
   int ret                             = 0;

   if (!playlist_curr)
      return 0;
   if (!menu)
      return menu_cbs_exit();

   /* Read current playlist parameters */
   playlist_get_index(playlist_curr, menu->rpl_entry_selection_ptr, &entry);

   /* Error checking
    * > If content path is empty, cannot do anything... */
   if (!string_is_empty(entry->path))
   {
      struct string_list *str_list = NULL;
      union string_list_elem_attr attr;
      char core_display_name[PATH_MAX_LENGTH];

      core_display_name[0] = '\0';

      /* Create string list container for playlist parameters */
      attr.i = 0;
      str_list = string_list_new();
      if (!str_list)
         return 0;

      /* Copy playlist parameters into string list
       *   [0]: content_path
       *   [1]: content_label
       *   [2]: core_path
       *   [3]: core_name
       *   [4]: crc32
       *   [5]: db_name */

      /* > content_path */
      string_list_append(str_list, entry->path, attr);

      /* > content_label */
      if (!string_is_empty(entry->label))
      {
         string_list_append(str_list, entry->label, attr);
      }
      else
      {
         /* Label is empty - use file name instead */
         char fallback_content_label[PATH_MAX_LENGTH];
         fallback_content_label[0] = '\0';
         fill_short_pathname_representation(fallback_content_label, entry->path, sizeof(fallback_content_label));
         string_list_append(str_list, fallback_content_label, attr);
      }

      /* > core_path + core_name */
      if (!string_is_empty(entry->core_path) && !string_is_empty(entry->core_name))
      {
         core_info_ctx_find_t core_info;

         /* >> core_path */
         string_list_append(str_list, entry->core_path, attr);

         /* >> core_name
          * (always use display name, if available) */
         core_info.inf  = NULL;
         core_info.path = entry->core_path;

         if (core_info_find(&core_info, entry->core_path))
            if (!string_is_empty(core_info.inf->display_name))
               strlcpy(core_display_name, core_info.inf->display_name, sizeof(core_display_name));

         if (!string_is_empty(core_display_name))
            string_list_append(str_list, core_display_name, attr);
         else
            string_list_append(str_list, entry->core_name, attr);
      }
      else
      {
         string_list_append(str_list, "DETECT", attr);
         string_list_append(str_list, "DETECT", attr);
      }

      /* crc32 */
      string_list_append(str_list, !string_is_empty(entry->crc32) ? entry->crc32 : "", attr);

      /* db_name */
      string_list_append(str_list, !string_is_empty(entry->db_name) ? entry->db_name : "", attr);

      /* Trigger 'ADD_TO_FAVORITES' event */
      if (!command_event(CMD_EVENT_ADD_TO_FAVORITES, (void*)str_list))
         ret = menu_cbs_exit();

      /* Clean up */
      string_list_free(str_list);
      str_list = NULL;
   }

   return ret;
}