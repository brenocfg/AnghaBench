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
struct retro_system_info {char* library_name; } ;
struct TYPE_8__ {char const* path_cheat_database; } ;
struct TYPE_9__ {TYPE_2__ paths; } ;
typedef  TYPE_3__ settings_t ;
typedef  int /*<<< orphan*/  s1 ;
struct TYPE_7__ {int /*<<< orphan*/  cheatfile; } ;
struct TYPE_10__ {TYPE_1__ name; } ;
typedef  TYPE_4__ global_t ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  core_get_system_info (struct retro_system_info*) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char*,char const*,size_t) ; 
 TYPE_4__* global_get_ptr () ; 
 char* path_basename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_valid (char*) ; 
 int /*<<< orphan*/  path_mkdir (char*) ; 
 scalar_t__ string_is_empty (char const*) ; 

__attribute__((used)) static bool cheat_manager_get_game_specific_filename(
      char *s, size_t len,
      bool saving)
{
   char s1[PATH_MAX_LENGTH];
   struct retro_system_info system_info;
   settings_t *settings    = config_get_ptr();
   global_t *global        = global_get_ptr();
   const char *core_name   = NULL;
   const char *game_name   = NULL;

   s1[0]                   = '\0';

   if (!settings || !global)
      return false;

   if (!core_get_system_info(&system_info))
      return false;

   core_name = system_info.library_name;
   game_name = path_basename(global->name.cheatfile);

   if (string_is_empty(settings->paths.path_cheat_database) ||
         string_is_empty(core_name) ||
         string_is_empty(game_name))
      return false;

   s[0] = '\0';

   fill_pathname_join(s1,
         settings->paths.path_cheat_database, core_name,
         sizeof(s1));

   if (saving)
   {
      /* Check if directory is valid, if not, create it */
      if (!path_is_valid(s1))
         path_mkdir(s1);
   }

   fill_pathname_join(s, s1, game_name, len);

   return true;
}