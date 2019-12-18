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
struct notifier_block {int dummy; } ;
struct netlink_notify {scalar_t__ protocol; scalar_t__ pid; int /*<<< orphan*/ * net; } ;

/* Variables and functions */
 scalar_t__ NETLINK_FIREWALL ; 
 unsigned long NETLINK_URELEASE ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  __ipq_reset () ; 
 int /*<<< orphan*/  init_net ; 
 scalar_t__ peer_pid ; 
 int /*<<< orphan*/  queue_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipq_rcv_nl_event(struct notifier_block *this,
		 unsigned long event, void *ptr)
{
	struct netlink_notify *n = ptr;

	if (event == NETLINK_URELEASE &&
	    n->protocol == NETLINK_FIREWALL && n->pid) {
		write_lock_bh(&queue_lock);
		if ((n->net == &init_net) && (n->pid == peer_pid))
			__ipq_reset();
		write_unlock_bh(&queue_lock);
	}
	return NOTIFY_DONE;
}