#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  config_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_MAIN_CONFIG ; 
 char* GLOBAL_CONFIG_DIR ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_ERR (char*,char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG ; 
 int /*<<< orphan*/  RARCH_WARN (char*,char*) ; 
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * config_file_new_alloc () ; 
 int /*<<< orphan*/ * config_file_new_from_path_to_string (char*) ; 
 int config_file_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 char* file_path_str (int /*<<< orphan*/ ) ; 
 int fill_pathname_application_data (char*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_application_dir (char*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_basedir (char*,char*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_home_dir (char*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char*,char*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_resolve_relative (char*,char*,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ malloc (int) ; 
 int path_mkdir (char*) ; 
 int /*<<< orphan*/  path_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static config_file_t *open_default_config_file(void)
{
   bool has_application_data              = false;
   size_t path_size                       = PATH_MAX_LENGTH * sizeof(char);
   char *application_data                 = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
   char *conf_path                        = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
   char *app_path                         = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
   config_file_t *conf                    = NULL;

   (void)has_application_data;
   (void)path_size;

   application_data[0] = conf_path[0] = app_path[0] = '\0';

#if defined(_WIN32) && !defined(_XBOX)
#if defined(__WINRT__) || defined(WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
   /* On UWP, the app install directory is not writable so use the writable LocalState dir instead */
   fill_pathname_home_dir(app_path, path_size);
#else
   fill_pathname_application_dir(app_path, path_size);
#endif
   fill_pathname_resolve_relative(conf_path, app_path,
         file_path_str(FILE_PATH_MAIN_CONFIG), path_size);

   conf = config_file_new_from_path_to_string(conf_path);

   if (!conf)
   {
      if (fill_pathname_application_data(application_data,
            path_size))
      {
         fill_pathname_join(conf_path, application_data,
               file_path_str(FILE_PATH_MAIN_CONFIG), path_size);
         conf = config_file_new_from_path_to_string(conf_path);
      }
   }

   if (!conf)
   {
      bool saved = false;

      /* Try to create a new config file. */
      conf = config_file_new_alloc();

      if (conf)
      {
         /* Since this is a clean config file, we can
          * safely use config_save_on_exit. */
         fill_pathname_resolve_relative(conf_path, app_path,
               file_path_str(FILE_PATH_MAIN_CONFIG), path_size);
         config_set_bool(conf, "config_save_on_exit", true);
         saved = config_file_write(conf, conf_path, true);
      }

      if (!saved)
      {
         /* WARN here to make sure user has a good chance of seeing it. */
         RARCH_ERR("Failed to create new config file in: \"%s\".\n",
               conf_path);
         goto error;
      }

      RARCH_WARN("Created new config file in: \"%s\".\n", conf_path);
   }
#elif defined(OSX)
   if (!fill_pathname_application_data(application_data,
            path_size))
      goto error;

   /* Group config file with menu configs, remaps, etc: */
   strlcat(application_data, "/config", path_size);

   path_mkdir(application_data);

   fill_pathname_join(conf_path, application_data,
         file_path_str(FILE_PATH_MAIN_CONFIG), path_size);
   conf = config_file_new_from_path_to_string(conf_path);

   if (!conf)
   {
      bool saved = false;
      conf       = config_file_new_alloc();

      if (conf)
      {
         config_set_bool(conf, "config_save_on_exit", true);
         saved = config_file_write(conf, conf_path, true);
      }

      if (!saved)
      {
         /* WARN here to make sure user has a good chance of seeing it. */
         RARCH_ERR("Failed to create new config file in: \"%s\".\n",
               conf_path);
         goto error;
      }

      RARCH_WARN("Created new config file in: \"%s\".\n", conf_path);
   }
#elif !defined(RARCH_CONSOLE)
   has_application_data =
      fill_pathname_application_data(application_data,
            path_size);

   if (has_application_data)
   {
      fill_pathname_join(conf_path, application_data,
            file_path_str(FILE_PATH_MAIN_CONFIG), path_size);
      RARCH_LOG("Looking for config in: \"%s\".\n", conf_path);
      conf = config_file_new_from_path_to_string(conf_path);
   }

   /* Fallback to $HOME/.retroarch.cfg. */
   if (!conf && getenv("HOME"))
   {
      fill_pathname_join(conf_path, getenv("HOME"),
            ".retroarch.cfg", path_size);
      RARCH_LOG("Looking for config in: \"%s\".\n", conf_path);
      conf = config_file_new_from_path_to_string(conf_path);
   }

   if (!conf && has_application_data)
   {
      bool dir_created = false;
      char *basedir    = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

      basedir[0]       = '\0';

      /* Try to create a new config file. */

      strlcpy(conf_path, application_data, path_size);

      fill_pathname_basedir(basedir, conf_path, path_size);

      fill_pathname_join(conf_path, conf_path,
            file_path_str(FILE_PATH_MAIN_CONFIG), path_size);

      dir_created = path_mkdir(basedir);
      free(basedir);

      if (dir_created)
      {
         char *skeleton_conf = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
         bool saved          = false;

         skeleton_conf[0] = '\0';

         /* Build a retroarch.cfg path from the 
          * global config directory (/etc). */
         fill_pathname_join(skeleton_conf, GLOBAL_CONFIG_DIR,
            file_path_str(FILE_PATH_MAIN_CONFIG), path_size);

         conf = config_file_new_from_path_to_string(skeleton_conf);
         if (conf)
            RARCH_WARN("Config: using skeleton config \"%s\" as base for a new config file.\n", skeleton_conf);
         else
            conf = config_file_new_alloc();

         free(skeleton_conf);

         if (conf)
         {
            /* Since this is a clean config file, we can 
             * safely use config_save_on_exit. */
            config_set_bool(conf, "config_save_on_exit", true);
            saved = config_file_write(conf, conf_path, true);
         }

         if (!saved)
         {
            /* WARN here to make sure user has a good chance of seeing it. */
            RARCH_ERR("Failed to create new config file in: \"%s\".\n", conf_path);
            goto error;
         }

         RARCH_WARN("Config: Created new config file in: \"%s\".\n", conf_path);
      }
   }
#endif

   (void)application_data;
   (void)conf_path;
   (void)app_path;

   if (!conf)
      goto error;

   path_set(RARCH_PATH_CONFIG, conf_path);
   free(application_data);
   free(conf_path);
   free(app_path);

   return conf;

error:
   if (conf)
      config_file_free(conf);
   free(application_data);
   free(conf_path);
   free(app_path);
   return NULL;
}