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
typedef  scalar_t__ u32 ;
struct tipc_msg {int dummy; } ;
struct tipc_port {struct tipc_msg phdr; scalar_t__ ref; int /*<<< orphan*/  max_pkt; void* usr_handle; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  nodesub_list; } ;
struct port {int last_in_seqno; int sent; void (* wakeup ) (struct tipc_port*) ;struct tipc_port publ; int /*<<< orphan*/  port_list; int /*<<< orphan*/  publications; int /*<<< orphan*/  timer; int /*<<< orphan*/ * user_port; scalar_t__ (* dispatcher ) (struct tipc_port*,struct sk_buff*) ;int /*<<< orphan*/ * congested_link; TYPE_1__ subscription; int /*<<< orphan*/  wait_list; } ;
typedef  int /*<<< orphan*/  Handler ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LONG_H_SIZE ; 
 int /*<<< orphan*/  MAX_PKT_DEFAULT ; 
 int /*<<< orphan*/  TIPC_NAMED_MSG ; 
 int /*<<< orphan*/  k_init_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct port*) ; 
 struct port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_init (struct tipc_msg*,scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_origport (struct tipc_msg*,scalar_t__) ; 
 scalar_t__ port_timeout ; 
 int /*<<< orphan*/  ports ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_port_list_lock ; 
 scalar_t__ tipc_ref_acquire (struct port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 

struct tipc_port *tipc_createport_raw(void *usr_handle,
			u32 (*dispatcher)(struct tipc_port *, struct sk_buff *),
			void (*wakeup)(struct tipc_port *),
			const u32 importance)
{
	struct port *p_ptr;
	struct tipc_msg *msg;
	u32 ref;

	p_ptr = kzalloc(sizeof(*p_ptr), GFP_ATOMIC);
	if (!p_ptr) {
		warn("Port creation failed, no memory\n");
		return NULL;
	}
	ref = tipc_ref_acquire(p_ptr, &p_ptr->publ.lock);
	if (!ref) {
		warn("Port creation failed, reference table exhausted\n");
		kfree(p_ptr);
		return NULL;
	}

	p_ptr->publ.usr_handle = usr_handle;
	p_ptr->publ.max_pkt = MAX_PKT_DEFAULT;
	p_ptr->publ.ref = ref;
	msg = &p_ptr->publ.phdr;
	msg_init(msg, importance, TIPC_NAMED_MSG, LONG_H_SIZE, 0);
	msg_set_origport(msg, ref);
	p_ptr->last_in_seqno = 41;
	p_ptr->sent = 1;
	INIT_LIST_HEAD(&p_ptr->wait_list);
	INIT_LIST_HEAD(&p_ptr->subscription.nodesub_list);
	p_ptr->congested_link = NULL;
	p_ptr->dispatcher = dispatcher;
	p_ptr->wakeup = wakeup;
	p_ptr->user_port = NULL;
	k_init_timer(&p_ptr->timer, (Handler)port_timeout, ref);
	spin_lock_bh(&tipc_port_list_lock);
	INIT_LIST_HEAD(&p_ptr->publications);
	INIT_LIST_HEAD(&p_ptr->port_list);
	list_add_tail(&p_ptr->port_list, &ports);
	spin_unlock_bh(&tipc_port_list_lock);
	return &(p_ptr->publ);
}