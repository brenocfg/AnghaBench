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
struct TYPE_3__ {int* state; } ;
typedef  TYPE_1__ x11_input_t ;
struct retro_keybind {int key; scalar_t__ valid; } ;
typedef  int int16_t ;
typedef  enum retro_key { ____Placeholder_retro_key } retro_key ;

/* Variables and functions */
 int RETROK_LAST ; 
 int /*<<< orphan*/  input_conv_analog_id_to_bind_id (unsigned int,unsigned int,unsigned int,unsigned int) ; 
 unsigned int* rarch_keysym_lut ; 

__attribute__((used)) static int16_t x_pressed_analog(x11_input_t *x11,
      const struct retro_keybind *binds, unsigned idx, unsigned id)
{
   int16_t pressed_minus = 0;
   int16_t pressed_plus  = 0;
   unsigned id_minus     = 0;
   unsigned id_plus      = 0;
   int id_minus_key      = 0;
   int id_plus_key       = 0;
   unsigned keycode      = 0;

   input_conv_analog_id_to_bind_id(idx, id, id_minus, id_plus);

   id_minus_key          = binds[id_minus].key;
   id_plus_key           = binds[id_plus].key;

   keycode               = rarch_keysym_lut[(enum retro_key)id_minus_key];
   if (      binds[id_minus].valid
         && (id_minus_key < RETROK_LAST)
         && (x11->state[keycode >> 3] & (1 << (keycode & 7))))
      pressed_minus = -0x7fff;

   keycode               = rarch_keysym_lut[(enum retro_key)id_plus_key];
   if (      binds[id_plus].valid
         && (id_plus_key < RETROK_LAST)
         && (x11->state[keycode >> 3] & (1 << (keycode & 7))))
      pressed_plus  =  0x7fff;

   return pressed_plus + pressed_minus;
}