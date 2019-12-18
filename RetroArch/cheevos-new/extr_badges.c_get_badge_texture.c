#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cheevos_badges_enable; } ;
struct TYPE_6__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  menu_texture_item ;
struct TYPE_7__ {int /*<<< orphan*/ * menu_texture_list; } ;

/* Variables and functions */
 TYPE_4__ badges_ctx ; 
 TYPE_2__* config_get_ptr () ; 

menu_texture_item get_badge_texture(int id)
{
   settings_t *settings = config_get_ptr();
   if (!settings || !settings->bools.cheevos_badges_enable)
      return (menu_texture_item)NULL;

   return badges_ctx.menu_texture_list[id];
}