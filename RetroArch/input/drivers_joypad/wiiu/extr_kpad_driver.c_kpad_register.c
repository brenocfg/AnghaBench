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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int get_slot_for_channel (unsigned int) ; 
 int /*<<< orphan*/  input_pad_connect (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kpad_deregister (unsigned int) ; 
 int /*<<< orphan*/  kpad_driver ; 
 TYPE_1__* wiimotes ; 

__attribute__((used)) static void kpad_register(unsigned channel, uint8_t device_type)
{
   if (wiimotes[channel].type != device_type)
   {
      int slot;

      kpad_deregister(channel);
      slot = get_slot_for_channel(channel);

      if(slot < 0)
      {
         RARCH_ERR("Couldn't get a slot for this remote.\n");
         return;
      }

      wiimotes[channel].type = device_type;
      input_pad_connect(slot, &kpad_driver);
   }
}