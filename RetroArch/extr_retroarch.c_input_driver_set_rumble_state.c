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
struct TYPE_2__ {int (* set_rumble ) (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* current_input ; 
 int /*<<< orphan*/  current_input_data ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 

bool input_driver_set_rumble_state(unsigned port,
      enum retro_rumble_effect effect, uint16_t strength)
{
   if (!current_input || !current_input->set_rumble)
      return false;
   return current_input->set_rumble(current_input_data,
         port, effect, strength);
}