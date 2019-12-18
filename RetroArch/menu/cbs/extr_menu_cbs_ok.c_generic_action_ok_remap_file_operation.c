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
struct retro_system_info {char* library_name; } ;
struct TYPE_4__ {char const* directory_input_remapping; } ;
struct TYPE_5__ {TYPE_1__ paths; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  file ;
typedef  int /*<<< orphan*/  directory ;
typedef  int /*<<< orphan*/  content_dir ;

/* Variables and functions */
#define  ACTION_OK_REMAP_FILE_REMOVE_CONTENT_DIR 133 
#define  ACTION_OK_REMAP_FILE_REMOVE_CORE 132 
#define  ACTION_OK_REMAP_FILE_REMOVE_GAME 131 
#define  ACTION_OK_REMAP_FILE_SAVE_CONTENT_DIR 130 
#define  ACTION_OK_REMAP_FILE_SAVE_CORE 129 
#define  ACTION_OK_REMAP_FILE_SAVE_GAME 128 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_ERROR_REMOVING_REMAP_FILE ; 
 int /*<<< orphan*/  MSG_ERROR_SAVING_REMAP_FILE ; 
 int /*<<< orphan*/  MSG_REMAP_FILE_REMOVED_SUCCESSFULLY ; 
 int /*<<< orphan*/  MSG_REMAP_FILE_SAVED_SUCCESSFULLY ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_CTL_IS_REMAPS_CONTENT_DIR_ACTIVE ; 
 int /*<<< orphan*/  RARCH_CTL_IS_REMAPS_CORE_ACTIVE ; 
 int /*<<< orphan*/  RARCH_CTL_IS_REMAPS_GAME_ACTIVE ; 
 int /*<<< orphan*/  RARCH_CTL_SET_REMAPS_CONTENT_DIR_ACTIVE ; 
 int /*<<< orphan*/  RARCH_CTL_SET_REMAPS_CORE_ACTIVE ; 
 int /*<<< orphan*/  RARCH_CTL_SET_REMAPS_GAME_ACTIVE ; 
 int /*<<< orphan*/  RARCH_CTL_UNSET_REMAPS_CONTENT_DIR_ACTIVE ; 
 int /*<<< orphan*/  RARCH_CTL_UNSET_REMAPS_CORE_ACTIVE ; 
 int /*<<< orphan*/  RARCH_CTL_UNSET_REMAPS_GAME_ACTIVE ; 
 int /*<<< orphan*/  RARCH_PATH_BASENAME ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char const*,char const*,int) ; 
 int /*<<< orphan*/  fill_pathname_parent_dir_name (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ input_remapping_remove_file (char*) ; 
 scalar_t__ input_remapping_save_file (char*) ; 
 int /*<<< orphan*/  input_remapping_set_defaults (int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_basename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_directory (char*) ; 
 int /*<<< orphan*/  path_mkdir (char*) ; 
 scalar_t__ rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct retro_system_info* runloop_get_libretro_system_info () ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

__attribute__((used)) static int generic_action_ok_remap_file_operation(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx,
      unsigned action_type)
{
   char directory[PATH_MAX_LENGTH];
   char file[PATH_MAX_LENGTH];
   char content_dir[PATH_MAX_LENGTH];
   settings_t *settings             = config_get_ptr();
   struct retro_system_info *system = runloop_get_libretro_system_info();
   const char *core_name            = system ? system->library_name : NULL;

   directory[0] = file[0]          = '\0';

   if (!string_is_empty(core_name))
      fill_pathname_join(
            directory,
            settings->paths.directory_input_remapping,
            core_name,
            sizeof(directory));

   switch (action_type)
   {
      case ACTION_OK_REMAP_FILE_SAVE_CORE:
      case ACTION_OK_REMAP_FILE_REMOVE_CORE:
         if (!string_is_empty(core_name))
            fill_pathname_join(file, core_name, core_name, sizeof(file));
         break;
      case ACTION_OK_REMAP_FILE_SAVE_GAME:
      case ACTION_OK_REMAP_FILE_REMOVE_GAME:
         if (!string_is_empty(core_name))
            fill_pathname_join(file, core_name,
                  path_basename(path_get(RARCH_PATH_BASENAME)), sizeof(file));
         break;
      case ACTION_OK_REMAP_FILE_SAVE_CONTENT_DIR:
      case ACTION_OK_REMAP_FILE_REMOVE_CONTENT_DIR:
         if (!string_is_empty(core_name))
         {
            fill_pathname_parent_dir_name(content_dir, path_get(RARCH_PATH_BASENAME), sizeof(content_dir));
            fill_pathname_join(file, core_name,
                  content_dir, sizeof(file));
         }
         break;
   }

   if (!path_is_directory(directory))
       path_mkdir(directory);

   if (action_type < ACTION_OK_REMAP_FILE_REMOVE_CORE)
   {
      if (input_remapping_save_file(file))
      {
         if (action_type == ACTION_OK_REMAP_FILE_SAVE_CORE)
            rarch_ctl(RARCH_CTL_SET_REMAPS_CORE_ACTIVE, NULL);
         else if (action_type == ACTION_OK_REMAP_FILE_SAVE_GAME)
            rarch_ctl(RARCH_CTL_SET_REMAPS_GAME_ACTIVE, NULL);
         else if (action_type == ACTION_OK_REMAP_FILE_SAVE_CONTENT_DIR)
            rarch_ctl(RARCH_CTL_SET_REMAPS_CONTENT_DIR_ACTIVE, NULL);

         runloop_msg_queue_push(
               msg_hash_to_str(MSG_REMAP_FILE_SAVED_SUCCESSFULLY),
               1, 100, true,
               NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      }
      else
         runloop_msg_queue_push(
               msg_hash_to_str(MSG_ERROR_SAVING_REMAP_FILE),
               1, 100, true,
               NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   }
   else
   {
      if (input_remapping_remove_file(file))
      {
         if (action_type == ACTION_OK_REMAP_FILE_REMOVE_CORE &&
               rarch_ctl(RARCH_CTL_IS_REMAPS_CORE_ACTIVE, NULL))
         {
            rarch_ctl(RARCH_CTL_UNSET_REMAPS_CORE_ACTIVE, NULL);
            input_remapping_set_defaults(true);
         }

         else if (action_type == ACTION_OK_REMAP_FILE_REMOVE_GAME &&
               rarch_ctl(RARCH_CTL_IS_REMAPS_GAME_ACTIVE, NULL))
         {
            rarch_ctl(RARCH_CTL_UNSET_REMAPS_GAME_ACTIVE, NULL);
            input_remapping_set_defaults(true);
         }

         else if (action_type == ACTION_OK_REMAP_FILE_REMOVE_CONTENT_DIR &&
               rarch_ctl(RARCH_CTL_IS_REMAPS_CONTENT_DIR_ACTIVE, NULL))
         {
            rarch_ctl(RARCH_CTL_UNSET_REMAPS_CONTENT_DIR_ACTIVE, NULL);
            input_remapping_set_defaults(true);
         }

         runloop_msg_queue_push(
               msg_hash_to_str(MSG_REMAP_FILE_REMOVED_SUCCESSFULLY),
               1, 100, true,
               NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      }
      else
         runloop_msg_queue_push(
               msg_hash_to_str(MSG_ERROR_REMOVING_REMAP_FILE),
               1, 100, true,
               NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   }
   return 0;
}