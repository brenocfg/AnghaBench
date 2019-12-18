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
typedef  int /*<<< orphan*/  rarch_joypad_info_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

__attribute__((used)) static int16_t nullinput_input_state(void *data,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind **retro_keybinds, unsigned port,
      unsigned device, unsigned idx, unsigned id)
{
   (void)data;
   (void)retro_keybinds;
   (void)port;
   (void)device;
   (void)idx;
   (void)id;

   return 0;
}