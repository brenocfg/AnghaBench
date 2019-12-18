#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  joypad; scalar_t__ controller; } ;
typedef  TYPE_1__ sdl_joypad_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_JoystickGetHat (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sdl_pad_get_button (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static uint8_t sdl_pad_get_hat(sdl_joypad_t *pad, unsigned hat)
{
#ifdef HAVE_SDL2
   if (pad->controller)
      return sdl_pad_get_button(pad, hat);
#endif
   return SDL_JoystickGetHat(pad->joypad, hat);
}