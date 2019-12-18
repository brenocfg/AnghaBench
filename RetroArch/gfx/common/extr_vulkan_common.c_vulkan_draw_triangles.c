#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ pipeline; int /*<<< orphan*/  mvp; void* sampler; void* view; int /*<<< orphan*/  dirty; } ;
struct TYPE_11__ {int /*<<< orphan*/  layout; } ;
struct TYPE_14__ {int /*<<< orphan*/  cmd; TYPE_3__ tracker; TYPE_2__ pipelines; TYPE_9__* context; TYPE_1__* chain; } ;
typedef  TYPE_5__ vk_t ;
struct vk_draw_triangles {scalar_t__ pipeline; int /*<<< orphan*/  vertices; TYPE_4__* vbo; int /*<<< orphan*/  sampler; int /*<<< orphan*/  texture; int /*<<< orphan*/  uniform_size; int /*<<< orphan*/  uniform; } ;
struct vk_buffer_range {int /*<<< orphan*/  offset; int /*<<< orphan*/  buffer; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  VkDescriptorSet ;
struct TYPE_15__ {int /*<<< orphan*/  device; } ;
struct TYPE_13__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  buffer; } ;
struct TYPE_10__ {int /*<<< orphan*/  descriptor_manager; int /*<<< orphan*/  ubo; } ;

/* Variables and functions */
 void* VK_NULL_HANDLE ; 
 int /*<<< orphan*/  VK_PIPELINE_BIND_POINT_GRAPHICS ; 
 int /*<<< orphan*/  VULKAN_DIRTY_DYNAMIC_BIT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vkCmdBindDescriptorSets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkCmdBindPipeline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vkCmdBindVertexBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkCmdDraw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vulkan_buffer_chain_alloc (TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vk_buffer_range*) ; 
 int /*<<< orphan*/  vulkan_check_dynamic_state (TYPE_5__*) ; 
 int /*<<< orphan*/  vulkan_descriptor_manager_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_transition_texture (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vulkan_write_quad_descriptors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vulkan_draw_triangles(vk_t *vk, const struct vk_draw_triangles *call)
{
   if (call->texture)
      vulkan_transition_texture(vk, vk->cmd, call->texture);

   if (call->pipeline != vk->tracker.pipeline)
   {
      vkCmdBindPipeline(vk->cmd,
            VK_PIPELINE_BIND_POINT_GRAPHICS, call->pipeline);
      vk->tracker.pipeline = call->pipeline;

      /* Changing pipeline invalidates dynamic state. */
      vk->tracker.dirty |= VULKAN_DIRTY_DYNAMIC_BIT;
   }

   vulkan_check_dynamic_state(vk);

   /* Upload descriptors */
   {
      VkDescriptorSet set;

      /* Upload UBO */
      struct vk_buffer_range range;
      if (!vulkan_buffer_chain_alloc(vk->context, &vk->chain->ubo,
               call->uniform_size, &range))
         return;

      memcpy(range.data, call->uniform, call->uniform_size);

      set = vulkan_descriptor_manager_alloc(
            vk->context->device,
            &vk->chain->descriptor_manager);

      vulkan_write_quad_descriptors(
            vk->context->device,
            set,
            range.buffer,
            range.offset,
            call->uniform_size,
            call->texture,
            call->sampler);

      vkCmdBindDescriptorSets(vk->cmd, VK_PIPELINE_BIND_POINT_GRAPHICS,
            vk->pipelines.layout, 0,
            1, &set, 0, NULL);

      vk->tracker.view = VK_NULL_HANDLE;
      vk->tracker.sampler = VK_NULL_HANDLE;
      memset(&vk->tracker.mvp, 0, sizeof(vk->tracker.mvp));
   }

   /* VBO is already uploaded. */
   vkCmdBindVertexBuffers(vk->cmd, 0, 1,
         &call->vbo->buffer, &call->vbo->offset);

   /* Draw the quad */
   vkCmdDraw(vk->cmd, call->vertices, 1, 0, 0);
}