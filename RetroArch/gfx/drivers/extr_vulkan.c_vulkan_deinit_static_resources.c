#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_7__* staging; } ;
struct TYPE_11__ {int /*<<< orphan*/  wait_dst_stages; int /*<<< orphan*/  cmd; } ;
struct TYPE_15__ {scalar_t__ memory; } ;
struct TYPE_10__ {TYPE_7__ blank_texture; } ;
struct TYPE_9__ {int /*<<< orphan*/  cache; } ;
struct TYPE_14__ {TYPE_5__ readback; TYPE_4__* context; TYPE_3__ hw; int /*<<< orphan*/  staging_pool; TYPE_2__ display; TYPE_1__ pipelines; } ;
typedef  TYPE_6__ vk_t ;
struct TYPE_12__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ VK_NULL_HANDLE ; 
 unsigned int VULKAN_MAX_SWAPCHAIN_IMAGES ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkDestroyCommandPool (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyPipelineCache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_destroy_texture (int /*<<< orphan*/ ,TYPE_7__*) ; 

__attribute__((used)) static void vulkan_deinit_static_resources(vk_t *vk)
{
   unsigned i;
   vkDestroyPipelineCache(vk->context->device,
         vk->pipelines.cache, NULL);
   vulkan_destroy_texture(
         vk->context->device,
         &vk->display.blank_texture);

   vkDestroyCommandPool(vk->context->device,
         vk->staging_pool, NULL);
   free(vk->hw.cmd);
   free(vk->hw.wait_dst_stages);

   for (i = 0; i < VULKAN_MAX_SWAPCHAIN_IMAGES; i++)
      if (vk->readback.staging[i].memory != VK_NULL_HANDLE)
         vulkan_destroy_texture(
               vk->context->device,
               &vk->readback.staging[i]);
}