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
typedef  int /*<<< orphan*/  SceAppUtilInitParam ;
typedef  int /*<<< orphan*/  SceAppUtilBootParam ;

/* Variables and functions */
 int /*<<< orphan*/  PSP_MEMORY_PARTITION_KERNEL ; 
 int /*<<< orphan*/  SCE_SYSMODULE_NET ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pspDebugScreenClear () ; 
 int /*<<< orphan*/  pspDebugScreenInit () ; 
 int /*<<< orphan*/  pspFpuSetEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pspSdkLoadStartModule (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_init () ; 
 int /*<<< orphan*/  sceAppUtilInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scePowerSetArmClockFrequency (int) ; 
 int /*<<< orphan*/  scePowerSetBusClockFrequency (int) ; 
 int /*<<< orphan*/  scePowerSetClockFrequency (int,int,int) ; 
 int /*<<< orphan*/  scePowerSetGpuClockFrequency (int) ; 
 int /*<<< orphan*/  scePowerSetGpuXbarClockFrequency (int) ; 
 int /*<<< orphan*/  sceSysmoduleLoadModule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_callback () ; 

__attribute__((used)) static void frontend_psp_init(void *data)
{
#ifndef IS_SALAMANDER

#ifdef VITA
   scePowerSetArmClockFrequency(444);
   scePowerSetBusClockFrequency(222);
   scePowerSetGpuClockFrequency(222);
   scePowerSetGpuXbarClockFrequency(166);
   sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
   
   SceAppUtilInitParam appUtilParam;
   SceAppUtilBootParam appUtilBootParam;
   memset(&appUtilParam, 0, sizeof(SceAppUtilInitParam));
   memset(&appUtilBootParam, 0, sizeof(SceAppUtilBootParam));
   sceAppUtilInit(&appUtilParam, &appUtilBootParam);
#else
   (void)data;
   /* initialize debug screen */
   pspDebugScreenInit();
   pspDebugScreenClear();

   setup_callback();

   pspFpuSetEnable(0); /* disable FPU exceptions */
   scePowerSetClockFrequency(333,333,166);
#endif
   pthread_init();

#endif

#if defined(HAVE_KERNEL_PRX) || defined(IS_SALAMANDER)
#ifndef VITA
   pspSdkLoadStartModule("kernel_functions.prx", PSP_MEMORY_PARTITION_KERNEL);
#endif
#endif
}