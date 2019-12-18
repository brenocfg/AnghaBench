#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int needs_update; TYPE_9__* vk; int /*<<< orphan*/  texture; int /*<<< orphan*/  texture_optimal; int /*<<< orphan*/  vertices; int /*<<< orphan*/  range; } ;
typedef  TYPE_4__ vulkan_raster_t ;
struct vk_draw_triangles {int uniform_size; int /*<<< orphan*/  vertices; int /*<<< orphan*/ * vbo; int /*<<< orphan*/ * uniform; int /*<<< orphan*/  sampler; int /*<<< orphan*/ * texture; int /*<<< orphan*/  pipeline; } ;
struct TYPE_18__ {int commandBufferCount; int /*<<< orphan*/ * pCommandBuffers; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ VkSubmitInfo ;
struct TYPE_19__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ VkCommandBufferBeginInfo ;
struct TYPE_20__ {int commandBufferCount; int /*<<< orphan*/  level; int /*<<< orphan*/  commandPool; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_7__ VkCommandBufferAllocateInfo ;
typedef  int /*<<< orphan*/  VkCommandBuffer ;
struct TYPE_15__ {int /*<<< orphan*/  mipmap_linear; } ;
struct TYPE_14__ {int /*<<< orphan*/  font; } ;
struct TYPE_21__ {int /*<<< orphan*/  staging_pool; TYPE_3__* context; int /*<<< orphan*/  mvp; TYPE_2__ samplers; TYPE_1__ pipelines; } ;
struct TYPE_16__ {int /*<<< orphan*/  device; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  VK_COMMAND_BUFFER_LEVEL_PRIMARY ; 
 int /*<<< orphan*/  VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT ; 
 int /*<<< orphan*/  VK_NULL_HANDLE ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_SUBMIT_INFO ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkAllocateCommandBuffers (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkBeginCommandBuffer (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  vkEndCommandBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkFreeCommandBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkQueueSubmit (int /*<<< orphan*/ ,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkQueueWaitIdle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vulkan_copy_staging_to_dynamic (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_draw_triangles (TYPE_9__*,struct vk_draw_triangles*) ; 

__attribute__((used)) static void vulkan_raster_font_flush(vulkan_raster_t *font)
{
   struct vk_draw_triangles call;

   call.pipeline     = font->vk->pipelines.font;
   call.texture      = &font->texture_optimal;
   call.sampler      = font->vk->samplers.mipmap_linear;
   call.uniform      = &font->vk->mvp;
   call.uniform_size = sizeof(font->vk->mvp);
   call.vbo          = &font->range;
   call.vertices     = font->vertices;

   if(font->needs_update)
   {
      VkCommandBuffer staging;
      VkSubmitInfo submit_info             = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
      VkCommandBufferAllocateInfo cmd_info = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
      VkCommandBufferBeginInfo begin_info  = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };

      cmd_info.commandPool        = font->vk->staging_pool;
      cmd_info.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
      cmd_info.commandBufferCount = 1;
      vkAllocateCommandBuffers(font->vk->context->device, &cmd_info, &staging);

      begin_info.flags            = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
      vkBeginCommandBuffer(staging, &begin_info);

      vulkan_copy_staging_to_dynamic(font->vk, staging,
            &font->texture_optimal, &font->texture);

      vkEndCommandBuffer(staging);

#ifdef HAVE_THREADS
      slock_lock(font->vk->context->queue_lock);
#endif

      submit_info.commandBufferCount = 1;
      submit_info.pCommandBuffers    = &staging;
      vkQueueSubmit(font->vk->context->queue,
            1, &submit_info, VK_NULL_HANDLE);

      vkQueueWaitIdle(font->vk->context->queue);

#ifdef HAVE_THREADS
      slock_unlock(font->vk->context->queue_lock);
#endif

      vkFreeCommandBuffers(font->vk->context->device,
            font->vk->staging_pool, 1, &staging);

      font->needs_update = false;
   }

   vulkan_draw_triangles(font->vk, &call);
}