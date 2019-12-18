#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ window; scalar_t__ display; } ;
struct TYPE_6__ {TYPE_1__ x11; } ;
struct TYPE_7__ {TYPE_2__ info; scalar_t__ window; int /*<<< orphan*/  version; } ;
typedef  TYPE_3__ SDL_SysWMinfo ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_DISPLAY_WIN32 ; 
 int /*<<< orphan*/  RARCH_DISPLAY_X11 ; 
 int SDL_GetWMInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  SDL_VERSION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_driver_display_set (uintptr_t) ; 
 int /*<<< orphan*/  video_driver_display_type_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_driver_window_set (uintptr_t) ; 

__attribute__((used)) static void sdl_gfx_set_handles(void)
{
   /* SysWMinfo headers are broken on OSX. */
#if defined(_WIN32) || defined(HAVE_X11)
   SDL_SysWMinfo info;
   SDL_VERSION(&info.version);

   if (SDL_GetWMInfo(&info) != 1)
      return;

#if defined(_WIN32)
   video_driver_display_type_set(RARCH_DISPLAY_WIN32);
   video_driver_display_set(0);
   video_driver_window_set((uintptr_t)info.window);
#elif defined(HAVE_X11)
   video_driver_display_type_set(RARCH_DISPLAY_X11);
   video_driver_display_set((uintptr_t)info.info.x11.display);
   video_driver_window_set((uintptr_t)info.info.x11.window);
#endif
#endif
}