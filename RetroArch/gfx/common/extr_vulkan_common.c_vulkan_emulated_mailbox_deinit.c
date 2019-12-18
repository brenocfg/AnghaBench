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
struct vulkan_emulated_mailbox {int dead; scalar_t__ cond; scalar_t__ lock; scalar_t__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vulkan_emulated_mailbox*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scond_free (scalar_t__) ; 
 int /*<<< orphan*/  scond_signal (scalar_t__) ; 
 int /*<<< orphan*/  slock_free (scalar_t__) ; 
 int /*<<< orphan*/  slock_lock (scalar_t__) ; 
 int /*<<< orphan*/  slock_unlock (scalar_t__) ; 
 int /*<<< orphan*/  sthread_join (scalar_t__) ; 

void vulkan_emulated_mailbox_deinit(struct vulkan_emulated_mailbox *mailbox)
{
   if (mailbox->thread)
   {
      slock_lock(mailbox->lock);
      mailbox->dead = true;
      scond_signal(mailbox->cond);
      slock_unlock(mailbox->lock);
      sthread_join(mailbox->thread);
   }

   if (mailbox->lock)
      slock_free(mailbox->lock);
   if (mailbox->cond)
      scond_free(mailbox->cond);

   memset(mailbox, 0, sizeof(*mailbox));
}