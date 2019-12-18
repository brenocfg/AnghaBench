#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum rarch_display_type { ____Placeholder_rarch_display_type } rarch_display_type ;
struct TYPE_6__ {int /*<<< orphan*/  ident; void* (* init ) () ;} ;

/* Variables and functions */
#define  RARCH_DISPLAY_WIN32 129 
#define  RARCH_DISPLAY_X11 128 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current_display_server ; 
 void* current_display_server_data ; 
 int /*<<< orphan*/  current_screen_orientation ; 
 TYPE_1__ dispserv_android ; 
 TYPE_1__ dispserv_null ; 
 TYPE_1__ dispserv_win32 ; 
 TYPE_1__ dispserv_x11 ; 
 int /*<<< orphan*/  initial_screen_orientation ; 
 void* stub1 () ; 
 int /*<<< orphan*/  video_display_server_destroy () ; 
 int /*<<< orphan*/  video_display_server_get_screen_orientation () ; 
 int video_driver_display_type_get () ; 

void* video_display_server_init(void)
{
   enum rarch_display_type type = video_driver_display_type_get();

   video_display_server_destroy();

   switch (type)
   {
      case RARCH_DISPLAY_WIN32:
#if defined(_WIN32) && !defined(_XBOX) && !defined(__WINRT__)
         current_display_server = &dispserv_win32;
#endif
         break;
      case RARCH_DISPLAY_X11:
#if defined(HAVE_X11)
         current_display_server = &dispserv_x11;
#endif
         break;
      default:
#if defined(ANDROID)
         current_display_server = &dispserv_android;
#else
         current_display_server = &dispserv_null;
#endif
         break;
   }

   current_display_server_data = current_display_server->init();

   RARCH_LOG("[Video]: Found display server: %s\n",
		   current_display_server->ident);

   initial_screen_orientation = video_display_server_get_screen_orientation();
   current_screen_orientation = initial_screen_orientation;

   return current_display_server_data;
}