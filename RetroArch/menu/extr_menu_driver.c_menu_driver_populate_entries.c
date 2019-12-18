#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  label; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ menu_displaylist_info_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* populate_entries ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_3__* menu_driver_ctx ; 
 int /*<<< orphan*/  menu_userdata ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void menu_driver_populate_entries(menu_displaylist_info_t *info)
{
   if (menu_driver_ctx && menu_driver_ctx->populate_entries)
      menu_driver_ctx->populate_entries(
            menu_userdata, info->path,
            info->label, info->type);
}