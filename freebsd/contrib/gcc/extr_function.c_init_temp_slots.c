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
 scalar_t__ avail_temp_slots ; 
 scalar_t__ temp_slot_level ; 
 scalar_t__ used_temp_slots ; 

void
init_temp_slots (void)
{
  /* We have not allocated any temporaries yet.  */
  avail_temp_slots = 0;
  used_temp_slots = 0;
  temp_slot_level = 0;
}