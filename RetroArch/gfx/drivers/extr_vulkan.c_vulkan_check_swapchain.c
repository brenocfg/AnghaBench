#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* context; } ;
typedef  TYPE_2__ vk_t ;
struct TYPE_7__ {int invalid_swapchain; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkQueueWaitIdle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vulkan_deinit_resources (TYPE_2__*) ; 
 int /*<<< orphan*/  vulkan_init_resources (TYPE_2__*) ; 
 int /*<<< orphan*/  vulkan_update_filter_chain (TYPE_2__*) ; 

__attribute__((used)) static void vulkan_check_swapchain(vk_t *vk)
{
   if (vk->context->invalid_swapchain)
   {
#ifdef HAVE_THREADS
      slock_lock(vk->context->queue_lock);
#endif
      vkQueueWaitIdle(vk->context->queue);
#ifdef HAVE_THREADS
      slock_unlock(vk->context->queue_lock);
#endif

      vulkan_deinit_resources(vk);
      vulkan_init_resources(vk);
      vk->context->invalid_swapchain = false;

      vulkan_update_filter_chain(vk);
   }
}