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
struct TYPE_4__ {char* library_name; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
typedef  TYPE_2__ rarch_system_info_t ;
typedef  int /*<<< orphan*/  content_dir_name ;
typedef  int /*<<< orphan*/  config_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_GAME_REMAP_FILE_LOADED ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_CTL_SET_REMAPS_CONTENT_DIR_ACTIVE ; 
 int /*<<< orphan*/  RARCH_CTL_SET_REMAPS_CORE_ACTIVE ; 
 int /*<<< orphan*/  RARCH_CTL_SET_REMAPS_GAME_ACTIVE ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 int /*<<< orphan*/  RARCH_PATH_BASENAME ; 
 int /*<<< orphan*/ * config_file_new_from_path_to_string (char*) ; 
 int /*<<< orphan*/  fill_pathname_join_special_ext (char*,char*,char const*,char const*,char*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_parent_dir_name (char*,char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ input_remapping_load_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_remapping_set_defaults (int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_basename (char const*) ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* runloop_get_system_info () ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

bool config_load_remap(const char *directory_input_remapping)
{
   size_t path_size                       = PATH_MAX_LENGTH * sizeof(char);
   config_file_t *new_conf                = NULL;
   char *remap_directory                  = NULL;
   char *core_path                        = NULL;
   char *game_path                        = NULL;
   char *content_path                     = NULL;
   rarch_system_info_t *system            = runloop_get_system_info();
   const char *core_name                  = system ? system->info.library_name : NULL;
   const char *rarch_path_basename        = path_get(RARCH_PATH_BASENAME);
   const char *game_name                  = path_basename(rarch_path_basename);
   char content_dir_name[PATH_MAX_LENGTH];

   if (string_is_empty(core_name) || string_is_empty(game_name))
      return false;

   /* Remap directory: remap_directory.
    * Try remap directory setting, no fallbacks defined */
   if (string_is_empty(directory_input_remapping))
      return false;

   if (!string_is_empty(rarch_path_basename))
      fill_pathname_parent_dir_name(content_dir_name,
            rarch_path_basename, sizeof(content_dir_name));

   /* path to the directory containing retroarch.cfg (prefix)    */
   remap_directory                        = (char*)
      malloc(PATH_MAX_LENGTH * sizeof(char));
   /* final path for core-specific configuration (prefix+suffix) */
   core_path                              = (char*)
      malloc(PATH_MAX_LENGTH * sizeof(char));
   /* final path for game-specific configuration (prefix+suffix) */
   game_path                              = (char*)
      malloc(PATH_MAX_LENGTH * sizeof(char));
   /* final path for content-dir-specific configuration (prefix+suffix) */
   content_path = (char*)
      malloc(PATH_MAX_LENGTH * sizeof(char));
   remap_directory[0] = core_path[0] = game_path[0] = '\0';

   strlcpy(remap_directory, directory_input_remapping, path_size);
   RARCH_LOG("[Remaps]: remap directory: %s\n", remap_directory);

   /* Concatenate strings into full paths for core_path, game_path */
   fill_pathname_join_special_ext(core_path,
         remap_directory, core_name,
         core_name,
         ".rmp",
         path_size);

   fill_pathname_join_special_ext(content_path,
         remap_directory, core_name,
         content_dir_name,
         ".rmp",
         path_size);

   fill_pathname_join_special_ext(game_path,
         remap_directory, core_name,
         game_name,
         ".rmp",
         path_size);

   input_remapping_set_defaults(false);

   /* If a game remap file exists, load it. */
   if ((new_conf = config_file_new_from_path_to_string(game_path)))
   {
      RARCH_LOG("[Remaps]: game-specific remap found at %s.\n", game_path);
      if (input_remapping_load_file(new_conf, game_path))
      {
         rarch_ctl(RARCH_CTL_SET_REMAPS_GAME_ACTIVE, NULL);
         goto success;
      }
   }

   /* If a content-dir remap file exists, load it. */
   if ((new_conf = config_file_new_from_path_to_string(content_path)))
   {
      RARCH_LOG("[Remaps]: content-dir-specific remap found at %s.\n", content_path);
      if (input_remapping_load_file(new_conf, content_path))
      {
         rarch_ctl(RARCH_CTL_SET_REMAPS_CONTENT_DIR_ACTIVE, NULL);
         goto success;
      }
   }

   /* If a core remap file exists, load it. */
   if ((new_conf = config_file_new_from_path_to_string(core_path)))
   {
      RARCH_LOG("[Remaps]: core-specific remap found at %s.\n", core_path);
      if (input_remapping_load_file(new_conf, core_path))
      {
         rarch_ctl(RARCH_CTL_SET_REMAPS_CORE_ACTIVE, NULL);
         goto success;
      }
   }

   new_conf = NULL;

   free(content_path);
   free(remap_directory);
   free(core_path);
   free(game_path);
   return false;

success:
   runloop_msg_queue_push(msg_hash_to_str(
            MSG_GAME_REMAP_FILE_LOADED), 1, 100, true,
         NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   free(content_path);
   free(remap_directory);
   free(core_path);
   free(game_path);
   return true;
}