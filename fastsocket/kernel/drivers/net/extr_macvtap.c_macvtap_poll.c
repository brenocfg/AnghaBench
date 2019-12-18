#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sk_receive_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  wait; } ;
struct macvtap_queue {TYPE_2__ sk; TYPE_1__ sock; } ;
struct file {struct macvtap_queue* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLERR ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int /*<<< orphan*/  SOCK_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ sock_writeable (TYPE_2__*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int macvtap_poll(struct file *file, poll_table * wait)
{
	struct macvtap_queue *q = file->private_data;
	unsigned int mask = POLLERR;

	if (!q)
		goto out;

	mask = 0;
	poll_wait(file, &q->sock.wait, wait);

	if (!skb_queue_empty(&q->sk.sk_receive_queue))
		mask |= POLLIN | POLLRDNORM;

	if (sock_writeable(&q->sk) ||
	    (!test_and_set_bit(SOCK_ASYNC_NOSPACE, &q->sock.flags) &&
	     sock_writeable(&q->sk)))
		mask |= POLLOUT | POLLWRNORM;

out:
	return mask;
}