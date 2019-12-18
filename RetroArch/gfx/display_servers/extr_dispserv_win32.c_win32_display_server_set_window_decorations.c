#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int decorations; } ;
typedef  TYPE_1__ dispserv_win32_t ;

/* Variables and functions */

__attribute__((used)) static bool win32_display_server_set_window_decorations(void *data, bool on)
{
   dispserv_win32_t *serv = (dispserv_win32_t*)data;

   if (serv)
      serv->decorations = on;

   /* menu_setting performs a reinit instead to properly
    * apply decoration changes */

   return true;
}