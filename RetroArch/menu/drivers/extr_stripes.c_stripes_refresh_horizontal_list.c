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
typedef  TYPE_1__ stripes_handle_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_MENU_CTL_SET_PREVENT_POPULATE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  file_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stripes_context_destroy_horizontal_list (TYPE_1__*) ; 
 int /*<<< orphan*/  stripes_context_reset_horizontal_list (TYPE_1__*) ; 
 int /*<<< orphan*/  stripes_free_list_nodes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stripes_init_horizontal_list (TYPE_1__*) ; 

__attribute__((used)) static void stripes_refresh_horizontal_list(stripes_handle_t *stripes)
{
   stripes_context_destroy_horizontal_list(stripes);
   if (stripes->horizontal_list)
   {
      stripes_free_list_nodes(stripes->horizontal_list, false);
      file_list_free(stripes->horizontal_list);
   }
   stripes->horizontal_list = NULL;

   menu_driver_ctl(RARCH_MENU_CTL_SET_PREVENT_POPULATE, NULL);

   stripes->horizontal_list         = (file_list_t*)
      calloc(1, sizeof(file_list_t));

   if (stripes->horizontal_list)
      stripes_init_horizontal_list(stripes);

   stripes_context_reset_horizontal_list(stripes);
}