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
typedef  int /*<<< orphan*/  uint32_t ;
struct delta_frame {int dummy; } ;
typedef  int /*<<< orphan*/  netplay_t ;
typedef  int /*<<< orphan*/  netplay_input_state_t ;

/* Variables and functions */
 unsigned int RETRO_DEVICE_ANALOG ; 
 unsigned int RETRO_DEVICE_JOYPAD ; 
 unsigned int RETRO_DEVICE_KEYBOARD ; 
 int /*<<< orphan*/  merge_analog_part (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct delta_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void netplay_merge_analog(netplay_t *netplay,
      netplay_input_state_t resstate, struct delta_frame *simframe,
      uint32_t device, uint32_t clients, unsigned dtype)
{
   /* Devices with no analog parts */
   if (dtype == RETRO_DEVICE_JOYPAD || dtype == RETRO_DEVICE_KEYBOARD)
      return;

   /* All other devices have at least one analog word */
   merge_analog_part(netplay, resstate, simframe, device, clients, 1, 0);
   merge_analog_part(netplay, resstate, simframe, device, clients, 1, 16);

   /* And the ANALOG device has two (two sticks) */
   if (dtype == RETRO_DEVICE_ANALOG)
   {
      merge_analog_part(netplay, resstate, simframe, device, clients, 2, 0);
      merge_analog_part(netplay, resstate, simframe, device, clients, 2, 16);
   }
}