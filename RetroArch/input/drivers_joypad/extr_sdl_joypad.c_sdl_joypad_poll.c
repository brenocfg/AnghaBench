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
struct TYPE_4__ {int /*<<< orphan*/  which; } ;
struct TYPE_5__ {int type; TYPE_1__ jdevice; } ;
typedef  TYPE_2__ SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_CONTROLLERDEVICEREMAPPED ; 
 int /*<<< orphan*/  SDL_FlushEvents (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GETEVENT ; 
 int /*<<< orphan*/  SDL_JOYAXISMOTION ; 
#define  SDL_JOYDEVICEADDED 129 
#define  SDL_JOYDEVICEREMOVED 128 
 int /*<<< orphan*/  SDL_JoystickUpdate () ; 
 scalar_t__ SDL_PeepEvents (TYPE_2__*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SDL_PumpEvents () ; 
 int /*<<< orphan*/  sdl_pad_connect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdl_pad_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdl_joypad_poll(void)
{
#ifdef HAVE_SDL2
   SDL_Event event;

   SDL_PumpEvents();

   while (SDL_PeepEvents(&event, 1,
            SDL_GETEVENT, SDL_JOYDEVICEADDED, SDL_JOYDEVICEREMOVED) > 0)
   {
      switch (event.type)
      {
         case SDL_JOYDEVICEADDED:
            sdl_pad_connect(event.jdevice.which);
            break;
         case SDL_JOYDEVICEREMOVED:
            sdl_pad_disconnect(event.jdevice.which);
            break;
      }
   }

   SDL_FlushEvents(SDL_JOYAXISMOTION, SDL_CONTROLLERDEVICEREMAPPED);
#else
   SDL_JoystickUpdate();
#endif
}