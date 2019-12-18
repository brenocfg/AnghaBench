#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  g_win; } ;
typedef  TYPE_1__ gfx_ctx_sdl_data_t ;

/* Variables and functions */
 unsigned int SDL_APPACTIVE ; 
 unsigned int SDL_APPINPUTFOCUS ; 
 unsigned int SDL_GetAppState () ; 
 unsigned int SDL_GetWindowFlags (int /*<<< orphan*/ ) ; 
 unsigned int SDL_WINDOW_INPUT_FOCUS ; 
 unsigned int SDL_WINDOW_MOUSE_FOCUS ; 

__attribute__((used)) static bool sdl_ctx_has_focus(void *data)
{
   unsigned flags;

#ifdef HAVE_SDL2
   gfx_ctx_sdl_data_t *sdl = (gfx_ctx_sdl_data_t*)data;
   flags = (SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
   return (SDL_GetWindowFlags(sdl->g_win) & flags) == flags;
#else
   flags = (SDL_APPINPUTFOCUS | SDL_APPACTIVE);
   return (SDL_GetAppState() & flags) == flags;
#endif
}