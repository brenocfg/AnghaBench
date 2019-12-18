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
typedef  int /*<<< orphan*/  sys_addr_t ;
typedef  int /*<<< orphan*/  spawn_data ;
typedef  int /*<<< orphan*/  SceNpDrmKey ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  SYS_PROCESS_PRIMARY_STACK_SIZE_1M ; 
 int sceNpDrmProcessExitSpawn (int /*<<< orphan*/ *,char const*,char const** const,char const**,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_game_process_exitspawn (char const*,char const** const,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int frontend_ps3_exec_exitspawn(const char *path,
      char const *argv[], char const *envp[])
{
   int ret;
   unsigned i;
   char spawn_data[256];
   SceNpDrmKey *license_data = NULL;

   for(i = 0; i < sizeof(spawn_data); ++i)
      spawn_data[i] = i & 0xff;

   ret = sceNpDrmProcessExitSpawn(license_data, path,
         (const char** const)argv, envp, (sys_addr_t)spawn_data,
         256, 1000, SYS_PROCESS_PRIMARY_STACK_SIZE_1M);

   if(ret <  0)
   {
      RARCH_WARN("SELF file is not of NPDRM type, trying another approach to boot it...\n");
      sys_game_process_exitspawn(path, (const char** const)argv,
            envp, NULL, 0, 1000, SYS_PROCESS_PRIMARY_STACK_SIZE_1M);
   }

   return ret;
}