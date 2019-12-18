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
 int* kbd_id ; 
 int kbd_num ; 

bool is_keyboard_id(int id)
{
   for(int i=0; i<kbd_num; i++)
      if (id == kbd_id[i]) return true;

   return false;
}