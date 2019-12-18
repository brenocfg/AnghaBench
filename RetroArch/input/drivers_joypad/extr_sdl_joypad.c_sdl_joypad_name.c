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
struct TYPE_2__ {scalar_t__ controller; } ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
 char const* SDL_GameControllerNameForIndex (unsigned int) ; 
 char const* SDL_JoystickName (unsigned int) ; 
 char const* SDL_JoystickNameForIndex (unsigned int) ; 
 TYPE_1__* sdl_pads ; 

__attribute__((used)) static const char *sdl_joypad_name(unsigned pad)
{
   if (pad >= MAX_USERS)
      return NULL;

#ifdef HAVE_SDL2
   if (sdl_pads[pad].controller)
      return SDL_GameControllerNameForIndex(pad);
   return SDL_JoystickNameForIndex(pad);
#else
   return SDL_JoystickName(pad);
#endif
}