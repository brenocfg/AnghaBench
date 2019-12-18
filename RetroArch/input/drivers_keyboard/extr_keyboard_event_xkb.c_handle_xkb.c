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
typedef  scalar_t__ xkb_mod_index_t ;
typedef  int /*<<< orphan*/  xkb_keysym_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  enum xkb_state_component { ____Placeholder_xkb_state_component } xkb_state_component ;

/* Variables and functions */
 unsigned int MOD_MAP_SIZE ; 
 int /*<<< orphan*/  RETROK_UNKNOWN ; 
 int /*<<< orphan*/  RETRO_DEVICE_KEYBOARD ; 
 int /*<<< orphan*/  XKB_KEY_DOWN ; 
 int /*<<< orphan*/  XKB_KEY_UP ; 
 scalar_t__ XKB_MOD_INVALID ; 
 scalar_t__ XKB_STATE_MODS_EFFECTIVE ; 
 int /*<<< orphan*/  input_keyboard_event (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_keymaps_translate_keysym_to_rk (int) ; 
 int /*<<< orphan*/ * mod_map_bit ; 
 int /*<<< orphan*/ * mod_map_idx ; 
 int /*<<< orphan*/  xkb_keysym_to_utf32 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  xkb_state ; 
 unsigned int xkb_state_key_get_syms (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**) ; 
 scalar_t__ xkb_state_mod_index_is_active (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  xkb_state_update_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int handle_xkb(int code, int value)
{
   unsigned i;
   const xkb_keysym_t *syms = NULL;
   unsigned num_syms        = 0;
   uint16_t mod             = 0;
   /* Convert Linux evdev to X11 (xkbcommon docs say so at least ...) */
   int xk_code              = code + 8;

   if (!xkb_state)
      return -1;

   if (value == 2) /* Repeat, release first explicitly. */
      xkb_state_update_key(xkb_state, xk_code, XKB_KEY_UP);

   if (value)
      num_syms = xkb_state_key_get_syms(xkb_state, xk_code, &syms);

   if (value > 0)
      xkb_state_update_key(xkb_state, xk_code, XKB_KEY_DOWN);
   else
      xkb_state_update_key(xkb_state, xk_code, XKB_KEY_UP);

   if (!syms)
      return -1;

   /* Build mod state. */
   for (i = 0; i < MOD_MAP_SIZE; i++)
   {
      xkb_mod_index_t *map_idx = (xkb_mod_index_t*)&mod_map_idx[i];
      uint16_t        *map_bit = (uint16_t       *)&mod_map_bit[i];

      if (*map_idx != XKB_MOD_INVALID)
         mod |= xkb_state_mod_index_is_active(
               xkb_state, *map_idx,
               (enum xkb_state_component)
               ((XKB_STATE_MODS_EFFECTIVE) > 0)) ? *map_bit : 0;
   }

   input_keyboard_event(value, input_keymaps_translate_keysym_to_rk(code),
         num_syms ? xkb_keysym_to_utf32(syms[0]) : 0, mod, RETRO_DEVICE_KEYBOARD);

   for (i = 1; i < num_syms; i++)
      input_keyboard_event(value, RETROK_UNKNOWN,
            xkb_keysym_to_utf32(syms[i]), mod, RETRO_DEVICE_KEYBOARD);

   return 0;
}