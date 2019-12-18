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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ input_small_keyboard_enable; scalar_t__ input_keyboard_gamepad_enable; } ;
struct TYPE_5__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
typedef  enum retro_mod { ____Placeholder_retro_mod } retro_mod ;

/* Variables and functions */
 unsigned int HIDKEY (unsigned int) ; 
 unsigned int MAX_KEYS ; 
 int* apple_key_state ; 
 TYPE_2__* config_get_ptr () ; 
 scalar_t__ handle_icade_event (unsigned int*,int*) ; 
 scalar_t__ handle_small_keyboard (unsigned int*,int) ; 
 int /*<<< orphan*/  input_keyboard_event (int,int /*<<< orphan*/ ,scalar_t__,int,unsigned int) ; 
 int /*<<< orphan*/  input_keymaps_translate_keysym_to_rk (unsigned int) ; 

void apple_input_keyboard_event(bool down,
      unsigned code, uint32_t character, uint32_t mod, unsigned device)
{
#if TARGET_OS_IPHONE
   settings_t *settings = config_get_ptr();
#endif

   code = HIDKEY(code);

#if TARGET_OS_IPHONE
   if (settings->bools.input_keyboard_gamepad_enable)
   {
      if (handle_icade_event(&code, &down))
         character = 0;
      else
         code      = 0;
   }
   else if (settings->bools.input_small_keyboard_enable)
   {
      if (handle_small_keyboard(&code, down))
         character = 0;
   }
#endif

   if (code == 0 || code >= MAX_KEYS)
      return;

   apple_key_state[code] = down;

   input_keyboard_event(down,
         input_keymaps_translate_keysym_to_rk(code),
         character, (enum retro_mod)mod, device);
}