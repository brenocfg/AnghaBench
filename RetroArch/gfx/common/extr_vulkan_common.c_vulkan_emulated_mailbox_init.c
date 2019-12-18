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
struct vulkan_emulated_mailbox {int /*<<< orphan*/  thread; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  swapchain; int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  VkSwapchainKHR ;
typedef  int /*<<< orphan*/  VkDevice ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vulkan_emulated_mailbox*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scond_new () ; 
 int /*<<< orphan*/  slock_new () ; 
 int /*<<< orphan*/  sthread_create (int /*<<< orphan*/ ,struct vulkan_emulated_mailbox*) ; 
 int /*<<< orphan*/  vulkan_emulated_mailbox_loop ; 

bool vulkan_emulated_mailbox_init(struct vulkan_emulated_mailbox *mailbox,
   VkDevice device,
   VkSwapchainKHR swapchain)
{
   memset(mailbox, 0, sizeof(*mailbox));
   mailbox->device = device;
   mailbox->swapchain = swapchain;

   mailbox->cond = scond_new();
   if (!mailbox->cond)
      return false;
   mailbox->lock = slock_new();
   if (!mailbox->lock)
      return false;
   mailbox->thread = sthread_create(vulkan_emulated_mailbox_loop, mailbox);
   if (!mailbox->thread)
      return false;
   return true;
}