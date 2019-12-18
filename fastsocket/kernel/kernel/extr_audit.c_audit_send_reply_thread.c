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
struct audit_reply {int /*<<< orphan*/  pid; int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_cmd_mutex ; 
 int /*<<< orphan*/  audit_sock ; 
 int /*<<< orphan*/  kfree (struct audit_reply*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlink_unicast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audit_send_reply_thread(void *arg)
{
	struct audit_reply *reply = (struct audit_reply *)arg;

	mutex_lock(&audit_cmd_mutex);
	mutex_unlock(&audit_cmd_mutex);

	/* Ignore failure. It'll only happen if the sender goes away,
	   because our timeout is set to infinite. */
	netlink_unicast(audit_sock, reply->skb, reply->pid, 0);
	kfree(reply);
	return 0;
}