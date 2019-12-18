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
typedef  int /*<<< orphan*/  Uint32 ;
struct TYPE_9__ {int ticks; int /*<<< orphan*/  sem_sync; } ;
struct TYPE_8__ {int frames_rendered; } ;
struct TYPE_6__ {int code; int /*<<< orphan*/ * data2; int /*<<< orphan*/ * data1; void* type; } ;
struct TYPE_7__ {TYPE_1__ user; void* type; } ;
typedef  TYPE_1__ SDL_UserEvent ;
typedef  TYPE_2__ SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_PushEvent (TYPE_2__*) ; 
 int /*<<< orphan*/  SDL_SemPost (int /*<<< orphan*/ ) ; 
 void* SDL_USEREVENT ; 
 TYPE_4__ sdl_sync ; 
 TYPE_3__ sdl_video ; 
 scalar_t__ vdp_pal ; 

__attribute__((used)) static Uint32 sdl_sync_timer_callback(Uint32 interval)
{
  SDL_SemPost(sdl_sync.sem_sync);
  sdl_sync.ticks++;
  if (sdl_sync.ticks == (vdp_pal ? 50 : 20))
  {
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = vdp_pal ? (sdl_video.frames_rendered / 3) : sdl_video.frames_rendered;
    userevent.data1 = NULL;
    userevent.data2 = NULL;
    sdl_sync.ticks = sdl_video.frames_rendered = 0;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
  }
  return interval;
}