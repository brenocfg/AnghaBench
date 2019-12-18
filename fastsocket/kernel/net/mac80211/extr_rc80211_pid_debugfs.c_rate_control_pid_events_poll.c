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
struct rc_pid_events_file_info {TYPE_1__* events; } ;
struct file {struct rc_pid_events_file_info* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_2__ {int /*<<< orphan*/  waitqueue; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int rate_control_pid_events_poll(struct file *file,
						 poll_table *wait)
{
	struct rc_pid_events_file_info *file_info = file->private_data;

	poll_wait(file, &file_info->events->waitqueue, wait);

	return POLLIN | POLLRDNORM;
}