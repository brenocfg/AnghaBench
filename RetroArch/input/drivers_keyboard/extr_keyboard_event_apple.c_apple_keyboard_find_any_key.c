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
typedef  size_t int32_t ;
struct TYPE_2__ {int hid_id; } ;

/* Variables and functions */
 TYPE_1__* apple_key_name_map ; 
 scalar_t__* apple_key_state ; 

int32_t apple_keyboard_find_any_key(void)
{
   unsigned i;

   for (i = 0; apple_key_name_map[i].hid_id; i++)
      if (apple_key_state[apple_key_name_map[i].hid_id])
         return apple_key_name_map[i].hid_id;

   return 0;
}