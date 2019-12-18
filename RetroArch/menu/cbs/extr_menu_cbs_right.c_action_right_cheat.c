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
 unsigned int MENU_SETTINGS_CHEAT_BEGIN ; 
 int generic_action_cheat_toggle (size_t,unsigned int,char const*,int) ; 

int action_right_cheat(unsigned type, const char *label,
      bool wraparound)
{
   size_t idx             = type - MENU_SETTINGS_CHEAT_BEGIN;
   return generic_action_cheat_toggle(idx, type, label,
         wraparound);
}