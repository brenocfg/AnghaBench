#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * horizontal_list; } ;
typedef  TYPE_1__ ozone_handle_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_MENU_CTL_SET_PREVENT_POPULATE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  file_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ozone_context_destroy_horizontal_list (TYPE_1__*) ; 
 int /*<<< orphan*/  ozone_context_reset_horizontal_list (TYPE_1__*) ; 
 int /*<<< orphan*/  ozone_free_list_nodes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ozone_init_horizontal_list (TYPE_1__*) ; 

void ozone_refresh_horizontal_list(ozone_handle_t *ozone)
{
   ozone_context_destroy_horizontal_list(ozone);
   if (ozone->horizontal_list)
   {
      ozone_free_list_nodes(ozone->horizontal_list, false);
      file_list_free(ozone->horizontal_list);
   }
   ozone->horizontal_list = NULL;

   menu_driver_ctl(RARCH_MENU_CTL_SET_PREVENT_POPULATE, NULL);

   ozone->horizontal_list         = (file_list_t*)
      calloc(1, sizeof(file_list_t));

   if (ozone->horizontal_list)
      ozone_init_horizontal_list(ozone);

   ozone_context_reset_horizontal_list(ozone);
}