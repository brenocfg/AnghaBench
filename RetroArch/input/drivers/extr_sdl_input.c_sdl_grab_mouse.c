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
typedef  int /*<<< orphan*/  SDL_Window ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_FALSE ; 
 int /*<<< orphan*/  SDL_SetWindowGrab (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_TRUE ; 
 scalar_t__ string_is_not_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  video_driver_get_ident () ; 
 scalar_t__ video_driver_get_ptr (int) ; 

__attribute__((used)) static void sdl_grab_mouse(void *data, bool state)
{
#ifdef HAVE_SDL2
   struct temp{
      SDL_Window *w;
   };

   if (string_is_not_equal(video_driver_get_ident(), "sdl2"))
      return;

   /* First member of sdl2_video_t is the window */
   SDL_SetWindowGrab(((struct temp*)video_driver_get_ptr(false))->w,
         state ? SDL_TRUE : SDL_FALSE);
#endif
}