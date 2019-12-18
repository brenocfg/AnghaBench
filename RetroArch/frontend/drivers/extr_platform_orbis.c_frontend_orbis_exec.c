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
typedef  int /*<<< orphan*/  argp ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void frontend_orbis_exec(const char *path, bool should_load_game)
{
   char argp[512] = {0};
   int   args = 0;

#ifndef IS_SALAMANDER
   if (should_load_game && !path_is_empty(RARCH_PATH_CONTENT))
   {
      argp[args] = '\0';
      strlcat(argp + args, path_get(RARCH_PATH_CONTENT), sizeof(argp) - args);
      args += strlen(argp + args) + 1;
   }
#endif

   RARCH_LOG("Attempt to load executable: [%s].\n", path);
   RARCH_LOG("Attempt to load executable: %d [%s].\n", args, argp);
   //int ret =  sceAppMgrLoadExec(path, args==0? NULL : (char * const*)((const char*[]){argp, 0}), NULL);
   //RARCH_LOG("Attempt to load executable: [%d].\n", ret);

}