#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int num_swapchain_images; TYPE_2__* swapchain; TYPE_1__* context; } ;
typedef  TYPE_3__ vk_t ;
struct TYPE_6__ {int /*<<< orphan*/  ubo; int /*<<< orphan*/  vbo; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  vulkan_buffer_chain_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_deinit_buffers(vk_t *vk)
{
   unsigned i;
   for (i = 0; i < vk->num_swapchain_images; i++)
   {
      vulkan_buffer_chain_free(
            vk->context->device, &vk->swapchain[i].vbo);
      vulkan_buffer_chain_free(
            vk->context->device, &vk->swapchain[i].ubo);
   }
}