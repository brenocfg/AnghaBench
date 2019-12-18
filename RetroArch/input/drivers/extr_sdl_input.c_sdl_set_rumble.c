#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  joypad; } ;
typedef  TYPE_1__ sdl_input_t ;
typedef  enum retro_rumble_effect { ____Placeholder_retro_rumble_effect } retro_rumble_effect ;

/* Variables and functions */
 int input_joypad_set_rumble (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sdl_set_rumble(void *data, unsigned port,
      enum retro_rumble_effect effect, uint16_t strength)
{
   sdl_input_t *sdl = (sdl_input_t*)data;
   if (!sdl)
      return false;
   return input_joypad_set_rumble(sdl->joypad, port, effect, strength);
}