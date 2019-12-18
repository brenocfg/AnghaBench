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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {char* directory_menu_config; } ;
struct TYPE_5__ {TYPE_1__ paths; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_CANNOT_INFER_NEW_CONFIG_PATH ; 
 int /*<<< orphan*/  MSG_CONFIG_DIRECTORY_NOT_SET ; 
 int /*<<< orphan*/  MSG_USING_CORE_NAME_FOR_NEW_CONFIG ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_ERR (char*,char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG ; 
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 int /*<<< orphan*/  RARCH_WARN (char*,char*) ; 
 int /*<<< orphan*/  command_event_save_config (char*,char*,int) ; 
 TYPE_2__* configuration_settings ; 
 int /*<<< orphan*/  fill_dated_filename (char*,char*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_base_noext (char*,char const*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_basedir (char*,char*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char*,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ path_is_valid (char const*) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int runloop_overrides_active ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 char* strdup (char*) ; 
 scalar_t__ string_is_empty (char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

__attribute__((used)) static bool command_event_save_core_config(void)
{
   char msg[128];
   bool found_path                 = false;
   bool overrides_active           = false;
   const char *core_path           = NULL;
   char *config_name               = NULL;
   char *config_path               = NULL;
   char *config_dir                = NULL;
   size_t config_size              = PATH_MAX_LENGTH * sizeof(char);
   settings_t *settings            = configuration_settings;

   msg[0]                          = '\0';

   if (settings && !string_is_empty(settings->paths.directory_menu_config))
      config_dir = strdup(settings->paths.directory_menu_config);
   else if (!path_is_empty(RARCH_PATH_CONFIG)) /* Fallback */
   {
      config_dir                   = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
      config_dir[0]                = '\0';
      fill_pathname_basedir(config_dir, path_get(RARCH_PATH_CONFIG),
            config_size);
   }

   if (string_is_empty(config_dir))
   {
      runloop_msg_queue_push(msg_hash_to_str(MSG_CONFIG_DIRECTORY_NOT_SET), 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      RARCH_ERR("[config] %s\n", msg_hash_to_str(MSG_CONFIG_DIRECTORY_NOT_SET));
      free (config_dir);
      return false;
   }

   core_path                       = path_get(RARCH_PATH_CORE);
   config_name                     = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
   config_path                     = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
   config_name[0]                  = '\0';
   config_path[0]                  = '\0';

   /* Infer file name based on libretro core. */
   if (path_is_valid(core_path))
   {
      unsigned i;
      RARCH_LOG("%s\n", msg_hash_to_str(MSG_USING_CORE_NAME_FOR_NEW_CONFIG));

      /* In case of collision, find an alternative name. */
      for (i = 0; i < 16; i++)
      {
         char tmp[64]   = {0};

         fill_pathname_base_noext(
               config_name,
               core_path,
               config_size);

         fill_pathname_join(config_path, config_dir, config_name,
               config_size);

         if (i)
            snprintf(tmp, sizeof(tmp), "-%u", i);

         strlcat(tmp, ".cfg", sizeof(tmp));
         strlcat(config_path, tmp, config_size);

         if (!path_is_valid(config_path))
         {
            found_path = true;
            break;
         }
      }
   }

   if (!found_path)
   {
      /* Fallback to system time... */
      RARCH_WARN("[config] %s\n",
            msg_hash_to_str(MSG_CANNOT_INFER_NEW_CONFIG_PATH));
      fill_dated_filename(config_name, ".cfg", config_size);
      fill_pathname_join(config_path, config_dir, config_name,
            config_size);
   }

   if (runloop_overrides_active)
   {
      /* Overrides block config file saving,
       * make it appear as overrides weren't enabled
       * for a manual save. */
      runloop_overrides_active = false;
      overrides_active         = true;
   }

   command_event_save_config(config_path, msg, sizeof(msg));

   if (!string_is_empty(msg))
      runloop_msg_queue_push(msg, 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

   if (overrides_active)
      runloop_overrides_active = true;
   else
      runloop_overrides_active = false;

   free(config_dir);
   free(config_name);
   free(config_path);
   return true;
}