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
struct venus_comm {int /*<<< orphan*/  vc_pending; int /*<<< orphan*/  vc_waitq; } ;
struct file {scalar_t__ private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int coda_psdev_poll(struct file *file, poll_table * wait)
{
        struct venus_comm *vcp = (struct venus_comm *) file->private_data;
	unsigned int mask = POLLOUT | POLLWRNORM;

	poll_wait(file, &vcp->vc_waitq, wait);
	if (!list_empty(&vcp->vc_pending))
                mask |= POLLIN | POLLRDNORM;

	return mask;
}