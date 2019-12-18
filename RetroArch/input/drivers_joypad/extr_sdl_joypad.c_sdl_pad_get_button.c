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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  joypad; scalar_t__ controller; } ;
typedef  TYPE_1__ sdl_joypad_t ;
typedef  int /*<<< orphan*/  SDL_GameControllerButton ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_GameControllerGetButton (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_JoystickGetButton (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static uint8_t sdl_pad_get_button(sdl_joypad_t *pad, unsigned button)
{
#ifdef HAVE_SDL2
   /* TODO: see if a LUT like xinput_joypad.c's button_index_to_bitmap_code is needed. */
   if (pad->controller)
      return SDL_GameControllerGetButton(pad->controller, (SDL_GameControllerButton)button);
#endif
   return SDL_JoystickGetButton(pad->joypad, button);
}