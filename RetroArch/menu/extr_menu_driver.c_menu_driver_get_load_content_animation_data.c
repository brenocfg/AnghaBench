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
typedef  int /*<<< orphan*/  menu_texture_item ;
struct TYPE_2__ {scalar_t__ (* get_load_content_animation_data ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ;} ;

/* Variables and functions */
 TYPE_1__* menu_driver_ctx ; 
 int /*<<< orphan*/  menu_userdata ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 

bool menu_driver_get_load_content_animation_data(menu_texture_item *icon, char **playlist_name)
{
   return menu_driver_ctx && menu_driver_ctx->get_load_content_animation_data
      && menu_driver_ctx->get_load_content_animation_data(menu_userdata, icon, playlist_name);
}