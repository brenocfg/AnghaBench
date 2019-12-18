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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_port {int dummy; } ;
struct sk_buff {struct sk_buff* next; } ;
typedef  int /*<<< orphan*/  Handler ;

/* Variables and functions */
 struct sk_buff* msg_queue_head ; 
 struct sk_buff* msg_queue_tail ; 
 scalar_t__ port_dispatcher_sigh ; 
 int /*<<< orphan*/  queue_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_k_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 port_dispatcher(struct tipc_port *dummy, struct sk_buff *buf)
{
	buf->next = NULL;
	spin_lock_bh(&queue_lock);
	if (msg_queue_head) {
		msg_queue_tail->next = buf;
		msg_queue_tail = buf;
	} else {
		msg_queue_tail = msg_queue_head = buf;
		tipc_k_signal((Handler)port_dispatcher_sigh, 0);
	}
	spin_unlock_bh(&queue_lock);
	return 0;
}