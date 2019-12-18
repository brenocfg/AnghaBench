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
struct TYPE_5__ {int quitting; } ;
typedef  TYPE_1__ sdl_video_t ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_2__ SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_GETEVENT ; 
 scalar_t__ SDL_PeepEvents (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_PumpEvents () ; 
 scalar_t__ SDL_QUIT ; 
 int /*<<< orphan*/  SDL_QUITMASK ; 

__attribute__((used)) static void sdl_gfx_check_window(sdl_video_t *vid)
{
   SDL_Event event;

   SDL_PumpEvents();
   while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_QUITMASK))
   {
      if (event.type != SDL_QUIT)
         continue;

      vid->quitting = true;
      break;
   }
}