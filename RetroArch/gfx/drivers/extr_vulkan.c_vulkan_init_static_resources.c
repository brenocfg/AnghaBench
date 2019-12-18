#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  blank_texture; } ;
struct TYPE_11__ {int /*<<< orphan*/  cache; } ;
struct TYPE_14__ {TYPE_3__ display; int /*<<< orphan*/  staging_pool; TYPE_2__* context; TYPE_1__ pipelines; } ;
typedef  TYPE_4__ vk_t ;
typedef  unsigned int uint32_t ;
struct TYPE_15__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ VkPipelineCacheCreateInfo ;
struct TYPE_16__ {int /*<<< orphan*/  queueFamilyIndex; int /*<<< orphan*/  flags; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ VkCommandPoolCreateInfo ;
struct TYPE_12__ {int /*<<< orphan*/  device; int /*<<< orphan*/  graphics_queue_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT ; 
 int /*<<< orphan*/  VK_FORMAT_B8G8R8A8_UNORM ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO ; 
 int /*<<< orphan*/  VULKAN_TEXTURE_STATIC ; 
 int /*<<< orphan*/  vkCreateCommandPool (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkCreatePipelineCache (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_create_texture (TYPE_4__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vulkan_init_static_resources(vk_t *vk)
{
   unsigned i;
   uint32_t blank[4 * 4];
   VkCommandPoolCreateInfo pool_info = {
      VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };

   /* Create the pipeline cache. */
   VkPipelineCacheCreateInfo cache   = {
      VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO };

   pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

   if (!vk->context)
      return;

   vkCreatePipelineCache(vk->context->device,
         &cache, NULL, &vk->pipelines.cache);

   pool_info.queueFamilyIndex = vk->context->graphics_queue_index;

   vkCreateCommandPool(vk->context->device,
         &pool_info, NULL, &vk->staging_pool);

   for (i = 0; i < 4 * 4; i++)
      blank[i] = -1u;

   vk->display.blank_texture = vulkan_create_texture(vk, NULL,
         4, 4, VK_FORMAT_B8G8R8A8_UNORM,
         blank, NULL, VULKAN_TEXTURE_STATIC);
}