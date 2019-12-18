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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_2__ {int /*<<< orphan*/  fifo; int /*<<< orphan*/  fifo_proc_list; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 scalar_t__ kfifo_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ sonypi_device ; 

__attribute__((used)) static unsigned int sonypi_misc_poll(struct file *file, poll_table *wait)
{
	poll_wait(file, &sonypi_device.fifo_proc_list, wait);
	if (kfifo_len(sonypi_device.fifo))
		return POLLIN | POLLRDNORM;
	return 0;
}