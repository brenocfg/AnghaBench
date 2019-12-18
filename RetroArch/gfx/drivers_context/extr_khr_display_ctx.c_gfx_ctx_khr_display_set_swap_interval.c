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
struct TYPE_3__ {int need_new_swapchain; scalar_t__ swapchain; } ;
struct TYPE_4__ {int swap_interval; TYPE_1__ vk; } ;
typedef  TYPE_2__ khr_display_ctx_data_t ;

/* Variables and functions */

__attribute__((used)) static void gfx_ctx_khr_display_set_swap_interval(void *data,
      int swap_interval)
{
   khr_display_ctx_data_t *khr = (khr_display_ctx_data_t*)data;

   if (khr->swap_interval != swap_interval)
   {
      khr->swap_interval = swap_interval;
      if (khr->vk.swapchain)
         khr->vk.need_new_swapchain = true;
   }
}