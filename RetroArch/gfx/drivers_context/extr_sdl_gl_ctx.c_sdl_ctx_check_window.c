#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int g_resized; unsigned int g_new_width; unsigned int g_new_height; } ;
typedef  TYPE_3__ gfx_ctx_sdl_data_t ;
struct TYPE_7__ {unsigned int w; unsigned int h; } ;
struct TYPE_6__ {unsigned int data1; unsigned int data2; int /*<<< orphan*/  event; } ;
struct TYPE_9__ {int type; TYPE_2__ resize; TYPE_1__ window; } ;
typedef  TYPE_4__ SDL_Event ;

/* Variables and functions */
#define  SDL_APP_TERMINATING 131 
 int /*<<< orphan*/  SDL_GETEVENT ; 
 scalar_t__ SDL_PeepEvents (TYPE_4__*,int,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  SDL_PumpEvents () ; 
#define  SDL_QUIT 130 
 int SDL_QUITMASK ; 
#define  SDL_VIDEORESIZE 129 
 int SDL_VIDEORESIZEMASK ; 
#define  SDL_WINDOWEVENT 128 
 int /*<<< orphan*/  SDL_WINDOWEVENT_RESIZED ; 

__attribute__((used)) static void sdl_ctx_check_window(void *data, bool *quit,
      bool *resize,unsigned *width,
      unsigned *height,
      bool is_shutdown)
{
   SDL_Event event;
   gfx_ctx_sdl_data_t *sdl = (gfx_ctx_sdl_data_t*)data;

   SDL_PumpEvents();

#ifdef HAVE_SDL2
   while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_QUIT, SDL_WINDOWEVENT) > 0)
#else
   while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_QUITMASK|SDL_VIDEORESIZEMASK) > 0)
#endif
   {
      switch (event.type)
      {
         case SDL_QUIT:
#ifdef HAVE_SDL2
         case SDL_APP_TERMINATING:
#endif
            *quit = true;
            break;
#ifdef HAVE_SDL2
         case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
               sdl->g_resized = true;
               sdl->g_new_width  = event.window.data1;
               sdl->g_new_height = event.window.data2;
            }
#else
         case SDL_VIDEORESIZE:
            sdl->g_resized = true;
            sdl->g_new_width  = event.resize.w;
            sdl->g_new_height = event.resize.h;
#endif
            break;
         default:
            break;
      }
   }

   if (sdl->g_resized)
   {
      *width    = sdl->g_new_width;
      *height   = sdl->g_new_height;
      *resize   = true;
      sdl->g_resized = false;
   }
}