#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  enum retro_key { ____Placeholder_retro_key } retro_key ;

/* Variables and functions */
 int* SDL_GetKeyState (int*) ; 
 int* SDL_GetKeyboardState (int*) ; 
 unsigned int SDL_GetScancodeFromKey (unsigned int) ; 
 unsigned int* rarch_keysym_lut ; 

__attribute__((used)) static bool sdl_key_pressed(int key)
{
   int num_keys;
#ifdef HAVE_SDL2
   const uint8_t *keymap = SDL_GetKeyboardState(&num_keys);
   unsigned sym          = SDL_GetScancodeFromKey(rarch_keysym_lut[(enum retro_key)key]);
#else
   const uint8_t *keymap = SDL_GetKeyState(&num_keys);
   unsigned sym          = rarch_keysym_lut[(enum retro_key)key];
#endif

   if (sym >= (unsigned)num_keys)
      return false;

   return keymap[sym];
}