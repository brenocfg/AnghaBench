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
typedef  int /*<<< orphan*/  menu_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/ * menu_driver_data ; 

menu_handle_t *menu_driver_get_ptr(void)
{
   return menu_driver_data;
}