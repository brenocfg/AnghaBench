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
typedef  enum retro_rumble_effect { ____Placeholder_retro_rumble_effect } retro_rumble_effect ;
struct TYPE_2__ {scalar_t__ sec_joypad; scalar_t__ joypad; } ;
typedef  TYPE_1__ cocoa_input_data_t ;

/* Variables and functions */
 int input_joypad_set_rumble (scalar_t__,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cocoa_input_set_rumble(void *data,
   unsigned port, enum retro_rumble_effect effect, uint16_t strength)
{
   cocoa_input_data_t *apple = (cocoa_input_data_t*)data;

   if (apple && apple->joypad)
      return input_joypad_set_rumble(apple->joypad,
            port, effect, strength);
#ifdef HAVE_MFI
    if (apple && apple->sec_joypad)
        return input_joypad_set_rumble(apple->sec_joypad,
            port, effect, strength);
#endif
   return false;
}