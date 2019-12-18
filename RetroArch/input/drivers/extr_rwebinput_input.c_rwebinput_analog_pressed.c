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
struct retro_keybind {int dummy; } ;
typedef  int /*<<< orphan*/  rwebinput_input_t ;
typedef  int /*<<< orphan*/  rarch_joypad_info_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_conv_analog_id_to_bind_id (unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ rwebinput_is_pressed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct retro_keybind const*,unsigned int,unsigned int) ; 

__attribute__((used)) static int16_t rwebinput_analog_pressed(rwebinput_input_t *rwebinput,
   rarch_joypad_info_t joypad_info, const struct retro_keybind *binds,
   unsigned idx, unsigned id)
{
   int16_t pressed_minus = 0, pressed_plus = 0;
   unsigned id_minus = 0;
   unsigned id_plus  = 0;

   input_conv_analog_id_to_bind_id(idx, id, id_minus, id_plus);

   if (rwebinput_is_pressed(rwebinput, joypad_info, binds, idx, id_minus))
      pressed_minus = -0x7fff;
   if (rwebinput_is_pressed(rwebinput, joypad_info, binds, idx, id_plus))
      pressed_plus = 0x7fff;

   return pressed_plus + pressed_minus;
}