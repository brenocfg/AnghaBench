#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
union string_list_elem_attr {int /*<<< orphan*/  i; } ;
struct string_list {int dummy; } ;
struct retro_subsystem_memory_info {char* extension; int /*<<< orphan*/  type; } ;
struct retro_subsystem_info {TYPE_2__* roms; int /*<<< orphan*/  num_roms; } ;
typedef  int /*<<< orphan*/  savename ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {TYPE_1__ subsystem; } ;
typedef  TYPE_5__ rarch_system_info_t ;
struct TYPE_13__ {char* savefile; } ;
struct TYPE_15__ {TYPE_4__ name; } ;
typedef  TYPE_6__ global_t ;
typedef  int /*<<< orphan*/  ext ;
struct TYPE_16__ {TYPE_3__* elems; scalar_t__ size; } ;
struct TYPE_12__ {char* data; } ;
struct TYPE_11__ {unsigned int num_memory; int /*<<< orphan*/ * memory; } ;

/* Variables and functions */
 unsigned int MIN (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  MSG_REDIRECTING_SAVEFILE_TO ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_DIR_CURRENT_SAVEFILE ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RARCH_OVERRIDE_SETTING_SAVE_PATH ; 
 int /*<<< orphan*/  RARCH_PATH_SUBSYSTEM ; 
 char* dir_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname (char*,char*,char*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_dir (char*,char*,char*,int) ; 
 int /*<<< orphan*/  fill_pathname_noext (char*,char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_6__ g_extern ; 
 struct retro_subsystem_info* libretro_find_subsystem_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ ) ; 
 scalar_t__ path_is_directory (char*) ; 
 int path_is_empty (int /*<<< orphan*/ ) ; 
 char* path_main_basename ; 
 int /*<<< orphan*/  path_remove_extension (char*) ; 
 int /*<<< orphan*/  retroarch_override_setting_is_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__ runloop_system ; 
 scalar_t__ savefile_ptr_get () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char*,union string_list_elem_attr) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 TYPE_7__* subsystem_fullpaths ; 

__attribute__((used)) static bool path_init_subsystem(void)
{
   unsigned i, j;
   const struct retro_subsystem_info *info = NULL;
   global_t   *global                      = &g_extern;
   rarch_system_info_t             *system = &runloop_system;
   bool subsystem_path_empty               = path_is_empty(RARCH_PATH_SUBSYSTEM);

   if (!system || subsystem_path_empty)
      return false;
   /* For subsystems, we know exactly which RAM types are supported. */

   info = libretro_find_subsystem_info(
         system->subsystem.data,
         system->subsystem.size,
         path_get(RARCH_PATH_SUBSYSTEM));

   /* We'll handle this error gracefully later. */
   if (info)
   {
      unsigned num_content = MIN(info->num_roms,
            subsystem_path_empty ?
            0 : (unsigned)subsystem_fullpaths->size);

      for (i = 0; i < num_content; i++)
      {
         for (j = 0; j < info->roms[i].num_memory; j++)
         {
            union string_list_elem_attr attr;
            char ext[32];
            char savename[PATH_MAX_LENGTH];
            size_t path_size = PATH_MAX_LENGTH * sizeof(char);
            char *path       = (char*)malloc(
                  PATH_MAX_LENGTH * sizeof(char));
            const struct retro_subsystem_memory_info *mem =
               (const struct retro_subsystem_memory_info*)
               &info->roms[i].memory[j];

            path[0] = ext[0] = '\0';

            snprintf(ext, sizeof(ext), ".%s", mem->extension);
            strlcpy(savename, subsystem_fullpaths->elems[i].data, sizeof(savename));
            path_remove_extension(savename);

            if (path_is_directory(dir_get(RARCH_DIR_CURRENT_SAVEFILE)))
            {
               /* Use SRAM dir */
               /* Redirect content fullpath to save directory. */
               strlcpy(path, dir_get(RARCH_DIR_CURRENT_SAVEFILE), path_size);
               fill_pathname_dir(path,
                     savename, ext,
                     path_size);
            }
            else
               fill_pathname(path, savename, ext, path_size);

            RARCH_LOG("%s \"%s\".\n",
               msg_hash_to_str(MSG_REDIRECTING_SAVEFILE_TO),
               path);

            attr.i = mem->type;
            string_list_append((struct string_list*)savefile_ptr_get(), path, attr);
            free(path);
         }
      }
   }

   if (global)
   {
      /* Let other relevant paths be inferred from the main SRAM location. */
      if (!retroarch_override_setting_is_set(RARCH_OVERRIDE_SETTING_SAVE_PATH, NULL))
         fill_pathname_noext(global->name.savefile,
               path_main_basename,
               ".srm",
               sizeof(global->name.savefile));

      if (path_is_directory(global->name.savefile))
      {
         fill_pathname_dir(global->name.savefile,
               path_main_basename,
               ".srm",
               sizeof(global->name.savefile));
         RARCH_LOG("%s \"%s\".\n",
               msg_hash_to_str(MSG_REDIRECTING_SAVEFILE_TO),
               global->name.savefile);
      }
   }

   return true;
}