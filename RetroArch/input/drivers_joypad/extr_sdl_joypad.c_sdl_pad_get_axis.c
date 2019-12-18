#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  joypad; scalar_t__ controller; } ;
typedef  TYPE_1__ sdl_joypad_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  SDL_GameControllerAxis ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_GameControllerGetAxis (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_JoystickGetAxis (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int16_t sdl_pad_get_axis(sdl_joypad_t *pad, unsigned axis)
{
#ifdef HAVE_SDL2
   /* TODO: see if a rarch <-> sdl translation is needed. */
   if (pad->controller)
      return SDL_GameControllerGetAxis(pad->controller, (SDL_GameControllerAxis)axis);
#endif
   return SDL_JoystickGetAxis(pad->joypad, axis);
}