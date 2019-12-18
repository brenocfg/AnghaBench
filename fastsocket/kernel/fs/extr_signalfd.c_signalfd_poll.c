#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct signalfd_ctx {int /*<<< orphan*/  sigmask; } ;
struct file {struct signalfd_ctx* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_6__ {TYPE_2__* sighand; TYPE_1__* signal; int /*<<< orphan*/  pending; } ;
struct TYPE_5__ {int /*<<< orphan*/  siglock; int /*<<< orphan*/  signalfd_wqh; } ;
struct TYPE_4__ {int /*<<< orphan*/  shared_pending; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 TYPE_3__* current ; 
 scalar_t__ next_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int signalfd_poll(struct file *file, poll_table *wait)
{
	struct signalfd_ctx *ctx = file->private_data;
	unsigned int events = 0;

	poll_wait(file, &current->sighand->signalfd_wqh, wait);

	spin_lock_irq(&current->sighand->siglock);
	if (next_signal(&current->pending, &ctx->sigmask) ||
	    next_signal(&current->signal->shared_pending,
			&ctx->sigmask))
		events |= POLLIN;
	spin_unlock_irq(&current->sighand->siglock);

	return events;
}