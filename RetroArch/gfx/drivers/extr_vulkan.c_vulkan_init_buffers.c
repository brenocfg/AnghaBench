#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned int num_swapchain_images; TYPE_4__* context; TYPE_1__* swapchain; } ;
typedef  TYPE_5__ vk_t ;
struct TYPE_9__ {int minUniformBufferOffsetAlignment; } ;
struct TYPE_8__ {TYPE_3__ limits; } ;
struct TYPE_10__ {TYPE_2__ gpu_properties; } ;
struct TYPE_7__ {void* ubo; void* vbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT ; 
 int /*<<< orphan*/  VK_BUFFER_USAGE_VERTEX_BUFFER_BIT ; 
 int /*<<< orphan*/  VULKAN_BUFFER_BLOCK_SIZE ; 
 void* vulkan_buffer_chain_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vulkan_init_buffers(vk_t *vk)
{
   unsigned i;
   for (i = 0; i < vk->num_swapchain_images; i++)
   {
      vk->swapchain[i].vbo = vulkan_buffer_chain_init(
            VULKAN_BUFFER_BLOCK_SIZE, 16, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
      vk->swapchain[i].ubo = vulkan_buffer_chain_init(
            VULKAN_BUFFER_BLOCK_SIZE,
            vk->context->gpu_properties.limits.minUniformBufferOffsetAlignment,
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
   }
}