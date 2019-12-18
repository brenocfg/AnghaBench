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
struct TYPE_2__ {int /*<<< orphan*/  joypad; } ;
typedef  TYPE_1__ x11_input_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  enum retro_rumble_effect { ____Placeholder_retro_rumble_effect } retro_rumble_effect ;

/* Variables and functions */
 int input_joypad_set_rumble (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool x_set_rumble(void *data, unsigned port,
      enum retro_rumble_effect effect, uint16_t strength)
{
   x11_input_t *x11 = (x11_input_t*)data;
   if (!x11)
      return false;
   return input_joypad_set_rumble(x11->joypad, port, effect, strength);
}