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
 unsigned int WIIU_WIIMOTE_CHANNELS ; 
 unsigned int* channel_slot_map ; 

__attribute__((used)) static int to_wiimote_channel(unsigned pad)
{
   unsigned i;

   for(i = 0; i < WIIU_WIIMOTE_CHANNELS; i++)
      if(channel_slot_map[i] == pad)
         return i;

   return -1;
}