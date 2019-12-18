#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int has_acquired_swapchain; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; int /*<<< orphan*/ * swapchain_semaphores; } ;
struct TYPE_8__ {scalar_t__ swapchain; TYPE_1__ context; } ;
typedef  TYPE_2__ gfx_ctx_vulkan_data_t ;
typedef  scalar_t__ VkResult ;
struct TYPE_9__ {int swapchainCount; scalar_t__* pSwapchains; unsigned int* pImageIndices; scalar_t__* pResults; int waitSemaphoreCount; int /*<<< orphan*/ * pWaitSemaphores; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ VkPresentInfoKHR ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 scalar_t__ VK_NULL_HANDLE ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_PRESENT_INFO_KHR ; 
 scalar_t__ VK_SUCCESS ; 
 int /*<<< orphan*/  retro_sleep (int) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trigger_spurious_error_vkresult (scalar_t__*) ; 
 scalar_t__ vkQueuePresentKHR (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  vulkan_destroy_swapchain (TYPE_2__*) ; 

void vulkan_present(gfx_ctx_vulkan_data_t *vk, unsigned index)
{
   VkPresentInfoKHR present           = { VK_STRUCTURE_TYPE_PRESENT_INFO_KHR };
   VkResult result                    = VK_SUCCESS;
   VkResult err                       = VK_SUCCESS;

   if (!vk->context.has_acquired_swapchain)
      return;
   vk->context.has_acquired_swapchain = false;

   /* We're still waiting for a proper swapchain, so just fake it. */
   if (vk->swapchain == VK_NULL_HANDLE)
   {
      retro_sleep(10);
      return;
   }

   present.swapchainCount          = 1;
   present.pSwapchains             = &vk->swapchain;
   present.pImageIndices           = &index;
   present.pResults                = &result;
   present.waitSemaphoreCount      = 1;
   present.pWaitSemaphores         = &vk->context.swapchain_semaphores[index];

   /* Better hope QueuePresent doesn't block D: */
#ifdef HAVE_THREADS
   slock_lock(vk->context.queue_lock);
#endif
   err = vkQueuePresentKHR(vk->context.queue, &present);

#ifdef WSI_HARDENING_TEST
   trigger_spurious_error_vkresult(&err);
#endif

   if (err != VK_SUCCESS || result != VK_SUCCESS)
   {
      RARCH_LOG("[Vulkan]: QueuePresent failed, destroying swapchain.\n");
      vulkan_destroy_swapchain(vk);
   }

#ifdef HAVE_THREADS
   slock_unlock(vk->context.queue_lock);
#endif
}