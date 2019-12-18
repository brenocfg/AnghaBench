#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int monitor_index; scalar_t__ windowed_fullscreen; } ;
typedef  TYPE_1__ video_frame_info_t ;
struct TYPE_5__ {unsigned int g_new_width; unsigned int g_new_height; int g_full; unsigned int g_width; unsigned int g_height; scalar_t__ g_ctx; scalar_t__ g_win; } ;
typedef  TYPE_2__ gfx_ctx_sdl_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_DISPLAY_OSX ; 
 int /*<<< orphan*/  RARCH_DISPLAY_WIN32 ; 
 int /*<<< orphan*/  RARCH_DISPLAY_X11 ; 
 int /*<<< orphan*/  RARCH_WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ SDL_CreateWindow (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 unsigned int SDL_FULLSCREEN ; 
 scalar_t__ SDL_GL_CreateContext (scalar_t__) ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 unsigned int SDL_OPENGL ; 
 scalar_t__ SDL_SetVideoMode (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SDL_SetWindowFullscreen (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  SDL_SetWindowSize (scalar_t__,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  SDL_WINDOWPOS_UNDEFINED_DISPLAY (unsigned int) ; 
 unsigned int SDL_WINDOW_FULLSCREEN ; 
 unsigned int SDL_WINDOW_FULLSCREEN_DESKTOP ; 
 unsigned int SDL_WINDOW_OPENGL ; 
 int /*<<< orphan*/  sdl2_set_handles (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_driver_set_video_cache_context_ack () ; 

__attribute__((used)) static bool sdl_ctx_set_video_mode(void *data,
      video_frame_info_t *video_info,
      unsigned width, unsigned height,
      bool fullscreen)
{
   unsigned fsflag         = 0;
   gfx_ctx_sdl_data_t *sdl = (gfx_ctx_sdl_data_t*)data;

   sdl->g_new_width  = width;
   sdl->g_new_height = height;

#ifdef HAVE_SDL2

   if (fullscreen)
   {
      if (video_info->windowed_fullscreen)
         fsflag = SDL_WINDOW_FULLSCREEN_DESKTOP;
      else
         fsflag = SDL_WINDOW_FULLSCREEN;
   }

   if (sdl->g_win)
   {
      SDL_SetWindowSize(sdl->g_win, width, height);

      if (fullscreen)
         SDL_SetWindowFullscreen(sdl->g_win, fsflag);
   }
   else
   {
      unsigned display = video_info->monitor_index;

      sdl->g_win = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED_DISPLAY(display),
                               SDL_WINDOWPOS_UNDEFINED_DISPLAY(display),
                               width, height, SDL_WINDOW_OPENGL | fsflag);
   }
#else
   if (fullscreen)
      fsflag = SDL_FULLSCREEN;

   sdl->g_win = SDL_SetVideoMode(width, height, 0, SDL_OPENGL | fsflag);
#endif

   if (!sdl->g_win)
      goto error;

#ifdef HAVE_SDL2
#if defined(_WIN32)
   sdl2_set_handles(sdl->g_win, RARCH_DISPLAY_WIN32);
#elif defined(HAVE_X11)
   sdl2_set_handles(sdl->g_win, RARCH_DISPLAY_X11);
#elif defined(HAVE_COCOA)
   sdl2_set_handles(sdl->g_win, RARCH_DISPLAY_OSX);
#endif

   if (sdl->g_ctx)
      video_driver_set_video_cache_context_ack();
   else
   {
      sdl->g_ctx = SDL_GL_CreateContext(sdl->g_win);

      if (!sdl->g_ctx)
         goto error;
   }
#endif

   sdl->g_full   = fullscreen;
   sdl->g_width  = width;
   sdl->g_height = height;

   return true;

error:
   RARCH_WARN("[SDL_GL]: Failed to set video mode: %s\n", SDL_GetError());
   return false;
}