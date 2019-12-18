#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ctx_data; TYPE_2__* ctx_driver; } ;
typedef  TYPE_4__ vk_t ;
struct TYPE_8__ {int video_swap_interval; } ;
struct TYPE_10__ {scalar_t__ video_adaptive_vsync; } ;
struct TYPE_12__ {TYPE_1__ uints; TYPE_3__ bools; } ;
typedef  TYPE_5__ settings_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* swap_interval ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_CTX_FLAGS_ADAPTIVE_VSYNC ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 TYPE_5__* config_get_ptr () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ video_driver_test_all_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vulkan_check_swapchain (TYPE_4__*) ; 

__attribute__((used)) static void vulkan_set_nonblock_state(void *data, bool state)
{
   int interval                = 0;
   vk_t *vk                    = (vk_t*)data;
   settings_t *settings        = config_get_ptr();
   bool adaptive_vsync_enabled = video_driver_test_all_flags(
         GFX_CTX_FLAGS_ADAPTIVE_VSYNC) && settings->bools.video_adaptive_vsync;

   if (!vk)
      return;

   RARCH_LOG("[Vulkan]: VSync => %s\n", state ? "off" : "on");

   if (!state)
      interval = settings->uints.video_swap_interval;

   if (vk->ctx_driver->swap_interval)
   {
      if (adaptive_vsync_enabled && interval == 1)
         interval = -1;
      vk->ctx_driver->swap_interval(vk->ctx_data, interval);
   }

   /* Changing vsync might require recreating the swapchain, which means new VkImages
    * to render into. */
   vulkan_check_swapchain(vk);
}