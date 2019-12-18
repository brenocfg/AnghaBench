#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {char* core_path; char* core_name; int /*<<< orphan*/  label; int /*<<< orphan*/  path; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  playlist_t ;
typedef  int /*<<< orphan*/  new_core_path ;
struct TYPE_7__ {size_t unsigned_var; } ;
struct TYPE_9__ {TYPE_1__ scratchpad; } ;
typedef  TYPE_3__ menu_handle_t ;
struct TYPE_10__ {char* path; TYPE_2__* inf; } ;
typedef  TYPE_4__ core_info_ctx_find_t ;
struct TYPE_8__ {char* display_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int PATH_MAX_LENGTH ; 
 int action_ok_file_load_with_detect_core (char const*,char const*,unsigned int,size_t,size_t) ; 
 int /*<<< orphan*/  command_playlist_update_write (int /*<<< orphan*/ *,size_t,struct playlist_entry*) ; 
 int /*<<< orphan*/  core_info_find (TYPE_4__*,char*) ; 
 int default_action_ok_load_content_from_playlist_from_menu (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int menu_cbs_exit () ; 
 int /*<<< orphan*/  menu_content_playlist_load (int /*<<< orphan*/ *,size_t) ; 
 TYPE_3__* menu_driver_get_ptr () ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 char* playlist_get_default_core_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  playlist_get_index (int /*<<< orphan*/ *,size_t,struct playlist_entry const**) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static int action_ok_playlist_entry_start_content(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   size_t selection_ptr                = 0;
   playlist_t *playlist                = playlist_get_cached();
   const struct playlist_entry *entry  = NULL;
   menu_handle_t *menu                 = menu_driver_get_ptr();

   if (!playlist || !menu)
      return menu_cbs_exit();

   selection_ptr                       = menu->scratchpad.unsigned_var;

   playlist_get_index(playlist, selection_ptr, &entry);

   if (     string_is_equal(entry->core_path, "DETECT")
         && string_is_equal(entry->core_name, "DETECT"))
   {
      core_info_ctx_find_t core_info;
      char new_core_path[PATH_MAX_LENGTH];
      const char *entry_path                 = NULL;
      const char *default_core_path          =
            playlist_get_default_core_path(playlist);
      bool found_associated_core             = false;

      new_core_path[0]                       = '\0';

      if (!string_is_empty(default_core_path))
      {
         strlcpy(new_core_path, default_core_path, sizeof(new_core_path));
         found_associated_core = true;
      }

      core_info.inf                          = NULL;
      core_info.path                         = new_core_path;

      if (!core_info_find(&core_info, new_core_path))
         found_associated_core = false;

      /* TODO: figure out if this should refer to
       * the inner or outer entry_path. */
      /* TODO: make sure there's only one entry_path
       * in this function. */
      if (!found_associated_core)
         return action_ok_file_load_with_detect_core(entry_path,
               label, type, selection_ptr, entry_idx);

      {
         struct playlist_entry entry = {0};

         entry.core_path = new_core_path;
         entry.core_name = core_info.inf->display_name;

         command_playlist_update_write(
               playlist,
               selection_ptr,
               &entry);
      }
   }

   if (!menu_content_playlist_load(playlist, selection_ptr))
   {
      runloop_msg_queue_push("File could not be loaded from playlist.\n", 1, 100, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      goto error;
   }

   playlist_get_index(playlist, selection_ptr, &entry);

   return default_action_ok_load_content_from_playlist_from_menu(entry->core_path, entry->path, entry->label);

error:
   return menu_cbs_exit();
}