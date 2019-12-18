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
typedef  enum menu_action { ____Placeholder_menu_action } menu_action ;

/* Variables and functions */

__attribute__((used)) static int null_menu_iterate(void *data, void *userdata, enum menu_action action)
{
   (void)data;
   (void)userdata;
   (void)action;

   return 1;
}