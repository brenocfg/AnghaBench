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
struct retro_keybind {scalar_t__ key; int /*<<< orphan*/  valid; } ;
struct TYPE_3__ {int* state; } ;
typedef  TYPE_1__ linuxraw_input_t ;
typedef  int int16_t ;
typedef  enum retro_key { ____Placeholder_retro_key } retro_key ;

/* Variables and functions */
 scalar_t__ RETROK_LAST ; 
 int /*<<< orphan*/  input_conv_analog_id_to_bind_id (unsigned int,unsigned int,unsigned int,unsigned int) ; 
 unsigned int* rarch_keysym_lut ; 

__attribute__((used)) static int16_t linuxraw_analog_pressed(linuxraw_input_t *linuxraw,
      const struct retro_keybind *binds, unsigned idx, unsigned id)
{
   const struct retro_keybind *bind_minus, *bind_plus;
   int16_t pressed_minus = 0, pressed_plus = 0;
   unsigned id_minus = 0;
   unsigned id_plus  = 0;

   input_conv_analog_id_to_bind_id(idx, id, id_minus, id_plus);

   bind_minus = &binds[id_minus];
   bind_plus  = &binds[id_plus];

   if (!bind_minus->valid || !bind_plus->valid)
      return 0;

   if (bind_minus->key < RETROK_LAST)
   {
      unsigned sym = rarch_keysym_lut[(enum retro_key)bind_minus->key];
      if (linuxraw->state[sym] & 0x80)
         pressed_minus = -0x7fff;
   }
   if (bind_plus->key  < RETROK_LAST)
   {
      unsigned sym = rarch_keysym_lut[(enum retro_key)bind_minus->key];
      if (linuxraw->state[sym] & 0x80)
         pressed_plus = 0x7fff;
   }

   return pressed_plus + pressed_minus;
}