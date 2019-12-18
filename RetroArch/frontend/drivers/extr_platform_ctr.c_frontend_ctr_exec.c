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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  error_string ;
typedef  int /*<<< orphan*/  errorConf ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_LANGUAGE_EN ; 
 int /*<<< orphan*/  DEBUG_STR (char const*) ; 
 int /*<<< orphan*/  DEBUG_VAR (char const*) ; 
 int /*<<< orphan*/  ERROR_TEXT ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*) ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 char* elf_path_cst ; 
 scalar_t__ envIsHomebrew () ; 
 int /*<<< orphan*/  errorDisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errorInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errorText (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  exec_3dsx_no_path_in_args (char const*,char const**) ; 
 int /*<<< orphan*/  exec_cia (char const*,char const**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_first_valid_core (char*) ; 
 char const* path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static void frontend_ctr_exec(const char* path, bool should_load_game)
{
   char game_path[PATH_MAX];
   const char* arg_data[3];
   errorConf error_dialog;
   char error_string[200 + PATH_MAX];
   int args           = 0;
   int error          = 0;

   DEBUG_VAR(path);
   DEBUG_STR(path);

   game_path[0]       = '\0';
   arg_data[0]        = NULL;

   arg_data[args]     = elf_path_cst;
   arg_data[args + 1] = NULL;
   args++;

   RARCH_LOG("Attempt to load core: [%s].\n", path);
#ifndef IS_SALAMANDER
   if (should_load_game && !path_is_empty(RARCH_PATH_CONTENT))
   {
      strcpy(game_path, path_get(RARCH_PATH_CONTENT));
      arg_data[args] = game_path;
      arg_data[args + 1] = NULL;
      args++;
      RARCH_LOG("content path: [%s].\n", path_get(RARCH_PATH_CONTENT));
   }
#endif

   if (path && path[0])
   {
#ifdef IS_SALAMANDER
      struct stat sbuff;
      bool file_exists = stat(path, &sbuff) == 0;

      if (!file_exists)
      {
         char core_path[PATH_MAX];

         core_path[0] = '\0';

         /* find first valid core and load it if the target core doesnt exist */
         get_first_valid_core(&core_path[0]);

         if (core_path[0] == '\0')
         {
            errorInit(&error_dialog, ERROR_TEXT, CFG_LANGUAGE_EN);
            errorText(&error_dialog, "There are no cores installed, install a core to continue.");
            errorDisp(&error_dialog);
            exit(0);
         }
      }
#endif

      if (envIsHomebrew())
         exec_3dsx_no_path_in_args(path, arg_data);
      else
      {
         RARCH_WARN("\n");
         RARCH_WARN("\n");
         RARCH_WARN("Warning:\n");
         RARCH_WARN("First core launch may take 20\n");
         RARCH_WARN("seconds! Do not force quit\n");
         RARCH_WARN("before then or your memory\n");
         RARCH_WARN("card may be corrupted!\n");
         RARCH_WARN("\n");
         RARCH_WARN("\n");
         exec_cia(path, arg_data);
      }

      errorInit(&error_dialog, ERROR_TEXT, CFG_LANGUAGE_EN);
      snprintf(error_string, sizeof(error_string),
            "Can't launch core:%s", path);
      errorText(&error_dialog, error_string);
      errorDisp(&error_dialog);
      exit(0); /* couldnt launch new core, but context 
                  is corrupt so we have to quit */
   }
}