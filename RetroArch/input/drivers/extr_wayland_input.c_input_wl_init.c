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
struct TYPE_3__ {int /*<<< orphan*/  joypad; } ;
typedef  TYPE_1__ input_ctx_wayland_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_joypad_init_driver (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  input_keymaps_init_keyboard_lut (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rarch_key_map_linux ; 

bool input_wl_init(void *data, const char *joypad_name)
{
   input_ctx_wayland_data_t *wl = (input_ctx_wayland_data_t*)data;

   if (!wl)
      return false;

   wl->joypad = input_joypad_init_driver(joypad_name, wl);

   if (!wl->joypad)
      return false;

   input_keymaps_init_keyboard_lut(rarch_key_map_linux);
   return true;
}