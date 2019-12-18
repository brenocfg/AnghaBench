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
 int /*<<< orphan*/  MENU_ACTION_RIGHT ; 
 int menu_setting_set (unsigned int,int /*<<< orphan*/ ,int) ; 

int bind_right_generic(unsigned type, const char *label,
       bool wraparound)
{
   return menu_setting_set(type, MENU_ACTION_RIGHT, wraparound);
}