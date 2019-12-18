#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vulkan_emulated_mailbox {scalar_t__ swapchain; int has_pending_request; int request_acquire; int acquired; scalar_t__ result; unsigned int index; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; } ;
typedef  scalar_t__ VkResult ;

/* Variables and functions */
 scalar_t__ VK_ERROR_OUT_OF_DATE_KHR ; 
 scalar_t__ VK_NULL_HANDLE ; 
 scalar_t__ VK_SUCCESS ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

VkResult vulkan_emulated_mailbox_acquire_next_image_blocking(
      struct vulkan_emulated_mailbox *mailbox,
      unsigned *index)
{
   VkResult res;
   if (mailbox->swapchain == VK_NULL_HANDLE)
      return VK_ERROR_OUT_OF_DATE_KHR;

   slock_lock(mailbox->lock);

   if (!mailbox->has_pending_request)
   {
      mailbox->request_acquire = true;
      scond_signal(mailbox->cond);
   }

   mailbox->has_pending_request = true;

   while (!mailbox->acquired)
      scond_wait(mailbox->cond, mailbox->lock);

   res = mailbox->result;
   if (res == VK_SUCCESS)
      *index = mailbox->index;
   mailbox->has_pending_request = false;
   mailbox->acquired = false;

   slock_unlock(mailbox->lock);
   return res;
}