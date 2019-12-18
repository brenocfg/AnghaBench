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
typedef  int uint16_t ;

/* Variables and functions */
 unsigned int DEFAULT_MAX_PADS ; 
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int,int) ; 
 int* pad_state ; 

__attribute__((used)) static bool switch_joypad_button(unsigned port_num, uint16_t key)
{
   if (port_num >= DEFAULT_MAX_PADS)
      return false;

#if 0
   RARCH_LOG("button(%d, %d)\n", port_num, key);
#endif

   return (pad_state[port_num] & (1 << key));
}