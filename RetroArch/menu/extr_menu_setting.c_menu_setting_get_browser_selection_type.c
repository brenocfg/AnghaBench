#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int browser_selection_type; } ;
typedef  TYPE_1__ rarch_setting_t ;
typedef  enum setting_type { ____Placeholder_setting_type } setting_type ;

/* Variables and functions */
 int ST_NONE ; 

enum setting_type menu_setting_get_browser_selection_type(rarch_setting_t *setting)
{
   if (!setting)
      return ST_NONE;
   return setting->browser_selection_type;
}