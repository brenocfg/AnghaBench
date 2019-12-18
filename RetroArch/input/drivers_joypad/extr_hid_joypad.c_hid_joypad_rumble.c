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
struct TYPE_2__ {int (* set_rumble ) (void*,unsigned int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* generic_hid ; 
 scalar_t__ hid_driver_get_data () ; 
 int stub1 (void*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hid_joypad_rumble(unsigned pad,
      enum retro_rumble_effect effect, uint16_t strength)
{
   if (generic_hid && generic_hid->set_rumble)
      return generic_hid->set_rumble((void*)hid_driver_get_data(), pad, effect, strength);
   return false;
}