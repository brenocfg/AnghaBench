#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {char* library_name; } ;
struct TYPE_6__ {TYPE_1__ info; } ;
typedef  TYPE_2__ rarch_system_info_t ;
typedef  int /*<<< orphan*/  Result ;

/* Variables and functions */
 int /*<<< orphan*/  AppletFocusHandlingMode_NoSuspend ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 scalar_t__ R_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appletHook (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appletInitializeGamePlayRecording () ; 
 int /*<<< orphan*/  appletIsGamePlayRecordingSupported (int*) ; 
 int /*<<< orphan*/  appletLockExit () ; 
 int /*<<< orphan*/  appletSetFocusHandlingMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  applet_hook_cookie ; 
 int /*<<< orphan*/  argb_to_rgba8 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkrstInitialize () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  frontend_switch_showsplash () ; 
 scalar_t__ hosversionBefore (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nifmInitialize () ; 
 int nxlinkStdio () ; 
 int nxlink_connected ; 
 int /*<<< orphan*/  on_applet_hook ; 
 int /*<<< orphan*/  pcvInitialize () ; 
 int /*<<< orphan*/  psmInitialize () ; 
 int psmInitialized ; 
 int /*<<< orphan*/  retro_get_system_info (TYPE_2__*) ; 
 int /*<<< orphan*/  rpng_load_image_argb (char const*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* runloop_get_system_info () ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  socketInitializeDefault () ; 
 scalar_t__ splashData ; 
 int /*<<< orphan*/  verbosity_enable () ; 

__attribute__((used)) static void frontend_switch_init(void *data)
{
#ifdef HAVE_LIBNX
   bool recording_supported      = false;
   uint32_t width                = 0;
   uint32_t height               = 0;

   nifmInitialize();
   
   if(hosversionBefore(8, 0, 0))
      pcvInitialize();
   else
      clkrstInitialize();

   appletLockExit();
   appletHook(&applet_hook_cookie, on_applet_hook, NULL);
   appletSetFocusHandlingMode(AppletFocusHandlingMode_NoSuspend);

   appletIsGamePlayRecordingSupported(&recording_supported);
   if(recording_supported)
      appletInitializeGamePlayRecording();

#ifdef NXLINK
   socketInitializeDefault();
   nxlink_connected = nxlinkStdio() != -1;
#ifndef IS_SALAMANDER
   verbosity_enable();
#endif /* IS_SALAMANDER */
#endif /* NXLINK */

   Result rc;
   rc = psmInitialize();
   if (R_SUCCEEDED(rc))
       psmInitialized = true;
   else
   {
       RARCH_WARN("Error initializing psm\n");
   }

#if 0
#ifndef HAVE_OPENGL
   /* Load splash */
   if (!splashData)
   {
      rarch_system_info_t *sys_info = runloop_get_system_info();
      retro_get_system_info(sys_info);

      if (sys_info)
      {
         const char *core_name       = sys_info->info.library_name;
         char *full_core_splash_path = (char*)malloc(PATH_MAX);

         snprintf(full_core_splash_path,
               PATH_MAX, "/retroarch/rgui/splash/%s.png", core_name);

         rpng_load_image_argb((const char *)
               full_core_splash_path, &splashData, &width, &height);

         if (splashData)
         {
            argb_to_rgba8(splashData, height, width);
            frontend_switch_showsplash();
         }
         else
         {
            rpng_load_image_argb(
                  "/retroarch/rgui/splash/RetroArch.png",
                  &splashData, &width, &height);

            if (splashData)
            {
               argb_to_rgba8(splashData, height, width);
               frontend_switch_showsplash();
            }
         }

         free(full_core_splash_path);
      }
      else
      {
         rpng_load_image_argb(
               "/retroarch/rgui/splash/RetroArch.png",
               &splashData, &width, &height);

         if (splashData)
         {
            argb_to_rgba8(splashData, height, width);
            frontend_switch_showsplash();
         }
      }
   }
   else
   {
      frontend_switch_showsplash();
   }
#endif
#endif

#endif /* HAVE_LIBNX (splash) */
}