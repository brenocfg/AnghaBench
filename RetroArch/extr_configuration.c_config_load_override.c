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

/* Variables and functions */
 int /*<<< orphan*/  APPLICATION_SPECIAL_DIRECTORY_CONFIG ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_CONFIG_OVERRIDE_LOADED ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  RARCH_OVERRIDE_SETTING_SAVE_PATH ; 
 int /*<<< orphan*/  RARCH_OVERRIDE_SETTING_STATE_PATH ; 
 int /*<<< orphan*/  RARCH_PATH_BASENAME ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG_APPEND ; 
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 scalar_t__ config_file_exists (char*) ; 
 int /*<<< orphan*/  config_get_ptr () ; 
 int /*<<< orphan*/  config_load_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_application_special (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_join_special_ext (char*,char*,char const*,char const*,char*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_parent_dir_name (char*,char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  global_get_ptr () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_basename (char const*) ; 
 int /*<<< orphan*/  path_clear (int /*<<< orphan*/ ) ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  retroarch_override_setting_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  retroarch_override_setting_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* runloop_get_system_info () ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

bool config_load_override(void)
{
   size_t path_size                       = PATH_MAX_LENGTH * sizeof(char);
   char *buf                              = NULL;
   char *core_path                        = NULL;
   char *game_path                        = NULL;
   char *content_path                     = NULL;
   char *config_directory                 = NULL;
   bool should_append                     = false;
   rarch_system_info_t *system            = runloop_get_system_info();
   const char *core_name                  = system ?
      system->info.library_name : NULL;
   const char *rarch_path_basename        = path_get(RARCH_PATH_BASENAME);
   const char *game_name                  = path_basename(rarch_path_basename);
   char content_dir_name[PATH_MAX_LENGTH];

   if (!string_is_empty(rarch_path_basename))
      fill_pathname_parent_dir_name(content_dir_name,
            rarch_path_basename, sizeof(content_dir_name));

   if (string_is_empty(core_name) || string_is_empty(game_name))
      return false;

   game_path                              = (char*)
      malloc(PATH_MAX_LENGTH * sizeof(char));
   core_path                              = (char*)
      malloc(PATH_MAX_LENGTH * sizeof(char));
   content_path = (char*)
      malloc(PATH_MAX_LENGTH * sizeof(char));
   buf                                    = (char*)
      malloc(PATH_MAX_LENGTH * sizeof(char));
   config_directory                       = (char*)
      malloc(PATH_MAX_LENGTH * sizeof(char));
   config_directory[0] = core_path[0] = game_path[0] = '\0';

   fill_pathname_application_special(config_directory, path_size,
         APPLICATION_SPECIAL_DIRECTORY_CONFIG);

   /* Concatenate strings into full paths for core_path, game_path, content_path */
   fill_pathname_join_special_ext(game_path,
         config_directory, core_name,
         game_name,
         ".cfg",
         path_size);

   fill_pathname_join_special_ext(content_path,
      config_directory, core_name,
      content_dir_name,
      ".cfg",
      path_size);

   fill_pathname_join_special_ext(core_path,
         config_directory, core_name,
         core_name,
         ".cfg",
         path_size);

   free(config_directory);

   /* per-core overrides */
   /* Create a new config file from core_path */
   if (config_file_exists(core_path))
   {
      RARCH_LOG("[Overrides] core-specific overrides found at %s.\n",
            core_path);

      path_set(RARCH_PATH_CONFIG_APPEND, core_path);

      should_append = true;
   }
   else
      RARCH_LOG("[Overrides] no core-specific overrides found at %s.\n",
            core_path);

   /* per-content-dir overrides */
   /* Create a new config file from content_path */
   if (config_file_exists(content_path))
   {
      char *temp_path = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

      temp_path[0]    = '\0';

      RARCH_LOG("[Overrides] content-dir-specific overrides found at %s.\n",
            game_path);

      if (should_append)
      {
         RARCH_LOG("[Overrides] content-dir-specific overrides stacking on top of previous overrides.\n");
         strlcpy(temp_path, path_get(RARCH_PATH_CONFIG_APPEND), path_size);
         strlcat(temp_path, "|", path_size);
         strlcat(temp_path, content_path, path_size);
      }
      else
         strlcpy(temp_path, content_path, path_size);

      path_set(RARCH_PATH_CONFIG_APPEND, temp_path);

      free(temp_path);

      should_append = true;
   }
   else
      RARCH_LOG("[Overrides] no content-dir-specific overrides found at %s.\n",
         content_path);

   /* per-game overrides */
   /* Create a new config file from game_path */
   if (config_file_exists(game_path))
   {
      char *temp_path = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

      temp_path[0]    = '\0';

      RARCH_LOG("[Overrides] game-specific overrides found at %s.\n",
            game_path);

      if (should_append)
      {
         RARCH_LOG("[Overrides] game-specific overrides stacking on top of previous overrides\n");
         strlcpy(temp_path, path_get(RARCH_PATH_CONFIG_APPEND), path_size);
         strlcat(temp_path, "|", path_size);
         strlcat(temp_path, game_path, path_size);
      }
      else
         strlcpy(temp_path, game_path, path_size);

      path_set(RARCH_PATH_CONFIG_APPEND, temp_path);

      free(temp_path);

      should_append = true;
   }
   else
      RARCH_LOG("[Overrides] no game-specific overrides found at %s.\n",
            game_path);

   if (!should_append)
      goto error;

   /* Re-load the configuration with any overrides
    * that might have been found */
   buf[0] = '\0';

   /* Store the libretro_path we're using since it will be
    * overwritten by the override when reloading. */
   strlcpy(buf, path_get(RARCH_PATH_CORE), path_size);

   /* Toggle has_save_path to false so it resets */
   retroarch_override_setting_unset(RARCH_OVERRIDE_SETTING_STATE_PATH, NULL);
   retroarch_override_setting_unset(RARCH_OVERRIDE_SETTING_SAVE_PATH,  NULL);

   if (!config_load_file(global_get_ptr(),
            path_get(RARCH_PATH_CONFIG), config_get_ptr()))
      goto error;

   /* Restore the libretro_path we're using
    * since it will be overwritten by the override when reloading. */
   path_set(RARCH_PATH_CORE, buf);
   runloop_msg_queue_push(msg_hash_to_str(MSG_CONFIG_OVERRIDE_LOADED),
         1, 100, true,
         NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

   /* Reset save paths. */
   retroarch_override_setting_set(RARCH_OVERRIDE_SETTING_STATE_PATH, NULL);
   retroarch_override_setting_set(RARCH_OVERRIDE_SETTING_SAVE_PATH, NULL);

   path_clear(RARCH_PATH_CONFIG_APPEND);

   free(buf);
   free(core_path);
   free(content_path);
   free(game_path);
   return true;

error:
   free(buf);
   free(core_path);
   free(content_path);
   free(game_path);
   return false;
}