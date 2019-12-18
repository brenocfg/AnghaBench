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
struct file {struct dev_data* private_data; } ;
struct dev_data {scalar_t__ state; scalar_t__ ev_next; int /*<<< orphan*/  lock; scalar_t__ setup_can_stall; scalar_t__ setup_in; scalar_t__ setup_abort; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 scalar_t__ STATE_DEV_SETUP ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
ep0_poll (struct file *fd, poll_table *wait)
{
       struct dev_data         *dev = fd->private_data;
       int                     mask = 0;

       poll_wait(fd, &dev->wait, wait);

       spin_lock_irq (&dev->lock);

       /* report fd mode change before acting on it */
       if (dev->setup_abort) {
               dev->setup_abort = 0;
               mask = POLLHUP;
               goto out;
       }

       if (dev->state == STATE_DEV_SETUP) {
               if (dev->setup_in || dev->setup_can_stall)
                       mask = POLLOUT;
       } else {
               if (dev->ev_next != 0)
                       mask = POLLIN;
       }
out:
       spin_unlock_irq(&dev->lock);
       return mask;
}