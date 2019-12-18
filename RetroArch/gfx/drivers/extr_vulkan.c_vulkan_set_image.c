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
struct TYPE_3__ {int num_semaphores; int valid_semaphore; scalar_t__ src_queue_family; int /*<<< orphan*/ * wait_dst_stages; int /*<<< orphan*/  const* semaphores; struct retro_vulkan_image const* image; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
typedef  TYPE_2__ vk_t ;
typedef  scalar_t__ uint32_t ;
struct retro_vulkan_image {int dummy; } ;
typedef  int /*<<< orphan*/  VkSemaphore ;
typedef  int /*<<< orphan*/  VkPipelineStageFlags ;

/* Variables and functions */
 int /*<<< orphan*/  VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_set_image(void *handle,
      const struct retro_vulkan_image *image,
      uint32_t num_semaphores,
      const VkSemaphore *semaphores,
      uint32_t src_queue_family)
{
   unsigned i;
   vk_t *vk              = (vk_t*)handle;

   vk->hw.image          = image;
   vk->hw.num_semaphores = num_semaphores;
   vk->hw.semaphores     = semaphores;

   if (num_semaphores > 0)
   {
      VkPipelineStageFlags *stage_flags = (VkPipelineStageFlags*)
         realloc(vk->hw.wait_dst_stages,
            sizeof(VkPipelineStageFlags) * vk->hw.num_semaphores);

      /* If this fails, we're screwed anyways. */
      retro_assert(stage_flags);

      vk->hw.wait_dst_stages = stage_flags;

      for (i = 0; i < vk->hw.num_semaphores; i++)
         vk->hw.wait_dst_stages[i] = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;

      vk->hw.valid_semaphore = true;
      vk->hw.src_queue_family = src_queue_family;
   }
}