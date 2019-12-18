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
struct sk_buff {int dummy; } ;
struct audit_netlink_list {int pid; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_cmd_mutex ; 
 int /*<<< orphan*/  audit_sock ; 
 int /*<<< orphan*/  kfree (struct audit_netlink_list*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlink_unicast (int /*<<< orphan*/ ,struct sk_buff*,int,int /*<<< orphan*/ ) ; 

int audit_send_list(void *_dest)
{
	struct audit_netlink_list *dest = _dest;
	int pid = dest->pid;
	struct sk_buff *skb;

	/* wait for parent to finish and send an ACK */
	mutex_lock(&audit_cmd_mutex);
	mutex_unlock(&audit_cmd_mutex);

	while ((skb = __skb_dequeue(&dest->q)) != NULL)
		netlink_unicast(audit_sock, skb, pid, 0);

	kfree(dest);

	return 0;
}