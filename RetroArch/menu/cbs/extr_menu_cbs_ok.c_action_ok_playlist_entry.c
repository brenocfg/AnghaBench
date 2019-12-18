#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {char* label; char* core_path; char* core_name; int /*<<< orphan*/  path; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  playlist_t ;
typedef  int /*<<< orphan*/  new_core_path ;
typedef  int /*<<< orphan*/  menu_handle_t ;
struct TYPE_5__ {char* path; TYPE_1__* inf; } ;
typedef  TYPE_2__ core_info_ctx_find_t ;
struct TYPE_4__ {char* display_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  PLAYLIST_LOAD ; 
 int action_ok_file_load_with_detect_core (int /*<<< orphan*/ ,char const*,unsigned int,size_t,size_t) ; 
 int /*<<< orphan*/  command_playlist_update_write (int /*<<< orphan*/ *,size_t,struct playlist_entry*) ; 
 int /*<<< orphan*/  core_info_find (TYPE_2__*,char*) ; 
 int default_action_ok_load_content_from_playlist_from_menu (char*,int /*<<< orphan*/ ,char const*) ; 
 int menu_cbs_exit () ; 
 int /*<<< orphan*/  menu_content_playlist_load (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * menu_driver_get_ptr () ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 char* playlist_get_default_core_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  playlist_get_index (int /*<<< orphan*/ *,size_t,struct playlist_entry const**) ; 
 int /*<<< orphan*/  playlist_resolve_path (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static int action_ok_playlist_entry(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   char new_core_path[PATH_MAX_LENGTH];
   size_t selection_ptr                = 0;
   playlist_t *playlist                = playlist_get_cached();
   const struct playlist_entry *entry  = NULL;
   const char *entry_label             = NULL;
   menu_handle_t *menu                 = menu_driver_get_ptr();

   new_core_path[0] = '\0';

   if (!playlist || !menu)
      return menu_cbs_exit();

   selection_ptr = entry_idx;

   playlist_get_index(playlist, selection_ptr, &entry);

   entry_label = entry->label;

   if (     string_is_equal(entry->core_path, "DETECT")
         && string_is_equal(entry->core_name, "DETECT"))
   {
      core_info_ctx_find_t core_info;
      const char *default_core_path          =
            playlist_get_default_core_path(playlist);
      bool found_associated_core             = false;

      if (!string_is_empty(default_core_path))
      {
         strlcpy(new_core_path, default_core_path, sizeof(new_core_path));
         playlist_resolve_path(PLAYLIST_LOAD, new_core_path, sizeof(new_core_path));
         found_associated_core = true;
      }

      core_info.inf                          = NULL;
      core_info.path                         = new_core_path;

      if (!core_info_find(&core_info, new_core_path))
         found_associated_core = false;

      if (!found_associated_core)
         /* TODO: figure out if this should refer to the inner or outer entry_path */
         /* TODO: make sure there's only one entry_path in this function */
         return action_ok_file_load_with_detect_core(entry->path,
               label, type, selection_ptr, entry_idx);

      {
         struct playlist_entry entry = {0};

         entry.core_path = (char*)default_core_path;
         entry.core_name = core_info.inf->display_name;

         command_playlist_update_write(NULL,
               selection_ptr,
               &entry);
      }

   }
   else if (!string_is_empty(entry->core_path)) {
       strlcpy(new_core_path, entry->core_path, sizeof(new_core_path));
       playlist_resolve_path(PLAYLIST_LOAD, new_core_path, sizeof(new_core_path));
   }

   if (!playlist || !menu_content_playlist_load(playlist, selection_ptr))
   {
      runloop_msg_queue_push(
            "File could not be loaded from playlist.\n",
            1, 100, true,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      return menu_cbs_exit();
   }

   playlist_get_index(playlist,
         selection_ptr, &entry);

   return default_action_ok_load_content_from_playlist_from_menu(
         new_core_path, entry->path, entry_label);
}