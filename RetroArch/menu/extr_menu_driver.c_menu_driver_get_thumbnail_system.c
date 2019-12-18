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
struct TYPE_2__ {int /*<<< orphan*/  (* get_thumbnail_system ) (int /*<<< orphan*/ ,char*,size_t) ;} ;

/* Variables and functions */
 TYPE_1__* menu_driver_ctx ; 
 int /*<<< orphan*/  menu_userdata ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,size_t) ; 

void menu_driver_get_thumbnail_system(char *s, size_t len)
{
   if (menu_driver_ctx && menu_driver_ctx->get_thumbnail_system)
      menu_driver_ctx->get_thumbnail_system(menu_userdata, s, len);
}