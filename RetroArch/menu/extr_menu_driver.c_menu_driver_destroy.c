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
 int /*<<< orphan*/ * menu_driver_ctx ; 
 int menu_driver_data_own ; 
 int menu_driver_pending_quick_menu ; 
 int menu_driver_prevent_populate ; 
 int /*<<< orphan*/ * menu_userdata ; 

void menu_driver_destroy(void)
{
   menu_driver_pending_quick_menu = false;
   menu_driver_prevent_populate   = false;
   menu_driver_data_own           = false;
   menu_driver_ctx                = NULL;
   menu_userdata                  = NULL;
}