#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int status; } ;
struct smu_private {scalar_t__ mode; int /*<<< orphan*/  lock; TYPE_1__ cmd; scalar_t__ busy; int /*<<< orphan*/  wait; } ;
struct file {struct smu_private* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ smu_file_commands ; 
 scalar_t__ smu_file_events ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int smu_fpoll(struct file *file, poll_table *wait)
{
	struct smu_private *pp = file->private_data;
	unsigned int mask = 0;
	unsigned long flags;

	if (pp == 0)
		return 0;

	if (pp->mode == smu_file_commands) {
		poll_wait(file, &pp->wait, wait);

		spin_lock_irqsave(&pp->lock, flags);
		if (pp->busy && pp->cmd.status != 1)
			mask |= POLLIN;
		spin_unlock_irqrestore(&pp->lock, flags);
	} if (pp->mode == smu_file_events) {
		/* Not yet implemented */
	}
	return mask;
}