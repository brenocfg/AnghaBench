#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int enable; int full_screen; } ;
struct TYPE_4__ {TYPE_1__ menu; } ;
typedef  TYPE_2__ vk_t ;

/* Variables and functions */

__attribute__((used)) static void vulkan_set_texture_enable(void *data, bool state, bool full_screen)
{
   vk_t *vk = (vk_t*)data;
   if (!vk)
      return;

   vk->menu.enable = state;
   vk->menu.full_screen = full_screen;
}