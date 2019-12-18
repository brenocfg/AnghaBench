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
struct SceKernelLoadExecVSHParam {int size; char* key; int unk5; scalar_t__ unk4; scalar_t__ configfile; int /*<<< orphan*/ * vshmain_args; scalar_t__ vshmain_args_size; void* argp; int /*<<< orphan*/  args; } ;
typedef  int /*<<< orphan*/  game_param ;
typedef  int /*<<< orphan*/  SceSize ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct SceKernelLoadExecVSHParam*,int /*<<< orphan*/ ,int) ; 
 int pspSdkSetK1 (int) ; 
 int sceKernelLoadExecVSHMs2 (char const*,struct SceKernelLoadExecVSHParam*) ; 
 scalar_t__ thread_active ; 

void exitspawn_kernel(const char *fileName, SceSize args, void *argp)
{
   struct SceKernelLoadExecVSHParam game_param;

   thread_active = 0;

   memset(&game_param,0,sizeof(game_param));

   game_param.size = sizeof(game_param);
   game_param.args = args;
   game_param.argp = argp;
   game_param.key  = "game";
   game_param.vshmain_args_size = 0;
   game_param.vshmain_args = NULL;
   game_param.configfile = 0;
   game_param.unk4 = 0;
   game_param.unk5 = 0x10000;

   int k1 = pspSdkSetK1(0);
   //sceKernelSuspendAllUserThreads();
   int ret = sceKernelLoadExecVSHMs2(fileName, &game_param);
   pspSdkSetK1(k1);
}