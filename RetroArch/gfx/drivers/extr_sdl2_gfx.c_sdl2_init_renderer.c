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
struct TYPE_4__ {scalar_t__ vsync; } ;
struct TYPE_5__ {int /*<<< orphan*/  renderer; int /*<<< orphan*/  window; TYPE_1__ video; } ;
typedef  TYPE_2__ sdl2_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_ClearHints () ; 
 int /*<<< orphan*/  SDL_CreateRenderer (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_HINT_OVERRIDE ; 
 int /*<<< orphan*/  SDL_HINT_RENDER_VSYNC ; 
 unsigned int SDL_RENDERER_ACCELERATED ; 
 unsigned int SDL_RENDERER_PRESENTVSYNC ; 
 int /*<<< orphan*/  SDL_SetHintWithPriority (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SetRenderDrawColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sdl2_init_renderer(sdl2_video_t *vid)
{
   unsigned flags = SDL_RENDERER_ACCELERATED;

   if (vid->video.vsync)
      flags |= SDL_RENDERER_PRESENTVSYNC;

   SDL_ClearHints();
   SDL_SetHintWithPriority(SDL_HINT_RENDER_VSYNC,
                           vid->video.vsync ? "1" : "0", SDL_HINT_OVERRIDE);
   vid->renderer = SDL_CreateRenderer(vid->window, -1, flags);

   if (!vid->renderer)
   {
      RARCH_ERR("[SDL2]: Failed to initialize renderer: %s", SDL_GetError());
      return;
   }

   SDL_SetRenderDrawColor(vid->renderer, 0, 0, 0, 255);
}