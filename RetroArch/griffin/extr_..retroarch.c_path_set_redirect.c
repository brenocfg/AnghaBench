#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct retro_system_info {char* library_name; } ;
struct TYPE_8__ {scalar_t__ savestates_in_content_dir; scalar_t__ savefiles_in_content_dir; scalar_t__ sort_savestates_enable; scalar_t__ sort_savefiles_enable; } ;
struct TYPE_10__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_9__ {char* savefile; char* savestate; char* cheatfile; } ;
struct TYPE_11__ {TYPE_2__ name; } ;
typedef  TYPE_4__ global_t ;
struct TYPE_12__ {struct retro_system_info info; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NO_CORE ; 
 int /*<<< orphan*/  MSG_REDIRECTING_CHEATFILE_TO ; 
 int /*<<< orphan*/  MSG_REDIRECTING_SAVEFILE_TO ; 
 int /*<<< orphan*/  MSG_REDIRECTING_SAVESTATE_TO ; 
 int /*<<< orphan*/  MSG_REVERTING_SAVEFILE_DIRECTORY_TO ; 
 int /*<<< orphan*/  MSG_REVERTING_SAVESTATE_DIRECTORY_TO ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_DIR_CURRENT_SAVEFILE ; 
 int /*<<< orphan*/  RARCH_DIR_CURRENT_SAVESTATE ; 
 int /*<<< orphan*/  RARCH_DIR_SAVEFILE ; 
 int /*<<< orphan*/  RARCH_DIR_SAVESTATE ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,char const*) ; 
 TYPE_3__* configuration_settings ; 
 char* dir_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fill_pathname_dir (char*,char*,char*,int) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char const*,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_4__ g_extern ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_basedir (char*) ; 
 scalar_t__ path_is_directory (char*) ; 
 char* path_main_basename ; 
 int /*<<< orphan*/  path_mkdir (char*) ; 
 TYPE_5__ runloop_system ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_is_equal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static void path_set_redirect(void)
{
   size_t path_size                            = PATH_MAX_LENGTH * sizeof(char);
   char *new_savefile_dir                      = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
   char *new_savestate_dir                     = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
   global_t   *global                          = &g_extern;
   const char *old_savefile_dir                = dir_get(RARCH_DIR_SAVEFILE);
   const char *old_savestate_dir               = dir_get(RARCH_DIR_SAVESTATE);
   struct retro_system_info *system            = &runloop_system.info;
   settings_t *settings                        = configuration_settings;

   new_savefile_dir[0] = new_savestate_dir[0]  = '\0';

   /* Initialize current save directories
    * with the values from the config. */
   strlcpy(new_savefile_dir,  old_savefile_dir,  path_size);
   strlcpy(new_savestate_dir, old_savestate_dir, path_size);

   if (system && !string_is_empty(system->library_name))
   {
#ifdef HAVE_MENU
      if (!string_is_equal(system->library_name,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NO_CORE)))
#endif
      {
         /* per-core saves: append the library_name to the save location */
         if (settings->bools.sort_savefiles_enable
               && !string_is_empty(old_savefile_dir))
         {
            fill_pathname_join(
                  new_savefile_dir,
                  old_savefile_dir,
                  system->library_name,
                  path_size);

            /* If path doesn't exist, try to create it,
             * if everything fails revert to the original path. */
            if (!path_is_directory(new_savefile_dir))
               if (!path_mkdir(new_savefile_dir))
               {
                  RARCH_LOG("%s %s\n",
                        msg_hash_to_str(MSG_REVERTING_SAVEFILE_DIRECTORY_TO),
                        old_savefile_dir);

                  strlcpy(new_savefile_dir, old_savefile_dir, path_size);
               }
         }

         /* per-core states: append the library_name to the save location */
         if (settings->bools.sort_savestates_enable
               && !string_is_empty(old_savestate_dir))
         {
            fill_pathname_join(
                  new_savestate_dir,
                  old_savestate_dir,
                  system->library_name,
                  path_size);

            /* If path doesn't exist, try to create it.
             * If everything fails, revert to the original path. */
            if (!path_is_directory(new_savestate_dir))
               if (!path_mkdir(new_savestate_dir))
               {
                  RARCH_LOG("%s %s\n",
                        msg_hash_to_str(MSG_REVERTING_SAVESTATE_DIRECTORY_TO),
                        old_savestate_dir);
                  strlcpy(new_savestate_dir,
                        old_savestate_dir,
                        path_size);
               }
         }
      }
   }

   /* Set savefile directory if empty to content directory */
   if (string_is_empty(new_savefile_dir) || settings->bools.savefiles_in_content_dir)
   {
      strlcpy(new_savefile_dir, path_main_basename,
            path_size);
      path_basedir(new_savefile_dir);
   }

   /* Set savestate directory if empty based on content directory */
   if (string_is_empty(new_savestate_dir) || settings->bools.savestates_in_content_dir)
   {
      strlcpy(new_savestate_dir, path_main_basename,
            path_size);
      path_basedir(new_savestate_dir);
   }

   if (global)
   {
      if (path_is_directory(new_savefile_dir))
         strlcpy(global->name.savefile, new_savefile_dir,
               sizeof(global->name.savefile));

      if (path_is_directory(new_savestate_dir))
         strlcpy(global->name.savestate, new_savestate_dir,
               sizeof(global->name.savestate));

      if (path_is_directory(global->name.savefile))
      {
         fill_pathname_dir(global->name.savefile,
               !string_is_empty(path_main_basename) ? path_main_basename :
                  system && !string_is_empty(system->library_name) ? system->library_name : "",
               ".srm",
               sizeof(global->name.savefile));
         RARCH_LOG("%s \"%s\".\n",
               msg_hash_to_str(MSG_REDIRECTING_SAVEFILE_TO),
               global->name.savefile);
      }

      if (path_is_directory(global->name.savestate))
      {
         fill_pathname_dir(global->name.savestate,
               !string_is_empty(path_main_basename) ? path_main_basename :
                  system && !string_is_empty(system->library_name) ? system->library_name : "",
               ".state",
               sizeof(global->name.savestate));
         RARCH_LOG("%s \"%s\".\n",
               msg_hash_to_str(MSG_REDIRECTING_SAVESTATE_TO),
               global->name.savestate);
      }

      if (path_is_directory(global->name.cheatfile))
      {
         /* FIXME: Should this optionally use system->library_name like the others? */
         fill_pathname_dir(global->name.cheatfile,
               !string_is_empty(path_main_basename) ? path_main_basename : "",
               ".state",
               sizeof(global->name.cheatfile));
         RARCH_LOG("%s \"%s\".\n",
               msg_hash_to_str(MSG_REDIRECTING_CHEATFILE_TO),
               global->name.cheatfile);
      }
   }

   dir_set(RARCH_DIR_CURRENT_SAVEFILE,  new_savefile_dir);
   dir_set(RARCH_DIR_CURRENT_SAVESTATE, new_savestate_dir);
   free(new_savefile_dir);
   free(new_savestate_dir);
}