#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vulkan_emulated_mailbox {int request_acquire; scalar_t__ result; int acquired; int /*<<< orphan*/  device; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  index; int /*<<< orphan*/  swapchain; scalar_t__ dead; } ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ VkFenceCreateInfo ;
typedef  int /*<<< orphan*/  VkFence ;

/* Variables and functions */
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  VK_NULL_HANDLE ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_FENCE_CREATE_INFO ; 
 scalar_t__ VK_SUCCESS ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ vkAcquireNextImageKHR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkCreateFence (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyFence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkResetFences (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkWaitForFences (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vulkan_emulated_mailbox_loop(void *userdata)
{
   VkFence fence;
   VkFenceCreateInfo info = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
   struct vulkan_emulated_mailbox *mailbox = (struct vulkan_emulated_mailbox*)userdata;

   if (!mailbox)
      return;

   vkCreateFence(mailbox->device, &info, NULL, &fence);

   for (;;)
   {
      slock_lock(mailbox->lock);
      while (!mailbox->dead && !mailbox->request_acquire)
         scond_wait(mailbox->cond, mailbox->lock);

      if (mailbox->dead)
      {
         slock_unlock(mailbox->lock);
         break;
      }

      mailbox->request_acquire = false;
      slock_unlock(mailbox->lock);

      mailbox->result = vkAcquireNextImageKHR(mailbox->device, mailbox->swapchain, UINT64_MAX,
            VK_NULL_HANDLE, fence, &mailbox->index);

      if (mailbox->result == VK_SUCCESS)
         vkWaitForFences(mailbox->device, 1, &fence, true, UINT64_MAX);
      vkResetFences(mailbox->device, 1, &fence);

      if (mailbox->result == VK_SUCCESS)
      {
         slock_lock(mailbox->lock);
         mailbox->acquired = true;
         scond_signal(mailbox->cond);
         slock_unlock(mailbox->lock);
      }
   }

   vkDestroyFence(mailbox->device, fence, NULL);
}