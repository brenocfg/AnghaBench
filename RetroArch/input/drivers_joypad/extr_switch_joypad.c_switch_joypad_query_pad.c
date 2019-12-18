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

/* Variables and functions */
 unsigned int DEFAULT_MAX_PADS ; 
 scalar_t__* pad_state ; 

__attribute__((used)) static bool switch_joypad_query_pad(unsigned pad)
{
   return pad < DEFAULT_MAX_PADS && pad_state[pad];
}