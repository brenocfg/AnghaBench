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
struct seq_file {struct mdstat_info* private; } ;
struct mdstat_info {scalar_t__ event; } ;
struct file {struct seq_file* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int POLLERR ; 
 int POLLIN ; 
 int POLLPRI ; 
 int POLLRDNORM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_event_count ; 
 int /*<<< orphan*/  md_event_waiters ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int mdstat_poll(struct file *filp, poll_table *wait)
{
	struct seq_file *m = filp->private_data;
	struct mdstat_info *mi = m->private;
	int mask;

	poll_wait(filp, &md_event_waiters, wait);

	/* always allow read */
	mask = POLLIN | POLLRDNORM;

	if (mi->event != atomic_read(&md_event_count))
		mask |= POLLERR | POLLPRI;
	return mask;
}