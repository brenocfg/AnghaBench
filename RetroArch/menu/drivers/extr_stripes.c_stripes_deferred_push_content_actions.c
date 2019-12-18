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
typedef  int /*<<< orphan*/  menu_displaylist_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLIST_HORIZONTAL_CONTENT_ACTIONS ; 
 int /*<<< orphan*/  menu_displaylist_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_displaylist_info_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_displaylist_process (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stripes_deferred_push_content_actions(menu_displaylist_info_t *info)
{
   if (!menu_displaylist_ctl(
         DISPLAYLIST_HORIZONTAL_CONTENT_ACTIONS, info))
      return -1;
   menu_displaylist_process(info);
   menu_displaylist_info_free(info);
   return 0;
}