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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ num_hats; scalar_t__ num_buttons; int /*<<< orphan*/  joypad; } ;
typedef  TYPE_1__ sdl_joypad_t ;

/* Variables and functions */
 scalar_t__ GET_HAT (scalar_t__) ; 
 unsigned int GET_HAT_DIR (scalar_t__) ; 
#define  HAT_DOWN_MASK 131 
#define  HAT_LEFT_MASK 130 
#define  HAT_RIGHT_MASK 129 
#define  HAT_UP_MASK 128 
 int SDL_HAT_DOWN ; 
 int SDL_HAT_LEFT ; 
 int SDL_HAT_RIGHT ; 
 int SDL_HAT_UP ; 
 scalar_t__ sdl_pad_get_button (TYPE_1__*,scalar_t__) ; 
 int sdl_pad_get_hat (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/ * sdl_pads ; 

__attribute__((used)) static bool sdl_joypad_button(unsigned port, uint16_t joykey)
{
   unsigned hat_dir  = 0;
   sdl_joypad_t *pad = (sdl_joypad_t*)&sdl_pads[port];
   if (!pad || !pad->joypad)
      return false;

   hat_dir = GET_HAT_DIR(joykey);
   /* Check hat. */
   if (hat_dir)
   {
      uint8_t  dir;
      uint16_t hat = GET_HAT(joykey);

      if (hat >= pad->num_hats)
         return false;

      dir = sdl_pad_get_hat(pad, hat);

      switch (hat_dir)
      {
         case HAT_UP_MASK:
            return dir & SDL_HAT_UP;
         case HAT_DOWN_MASK:
            return dir & SDL_HAT_DOWN;
         case HAT_LEFT_MASK:
            return dir & SDL_HAT_LEFT;
         case HAT_RIGHT_MASK:
            return dir & SDL_HAT_RIGHT;
         default:
            break;
      }
      return false;
   }

   /* Check the button */
   if (joykey < pad->num_buttons && sdl_pad_get_button(pad, joykey))
      return true;

   return false;
}