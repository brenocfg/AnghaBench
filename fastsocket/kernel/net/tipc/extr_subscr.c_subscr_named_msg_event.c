#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unchar ;
typedef  scalar_t__ u32 ;
struct tipc_portid {int dummy; } ;
struct tipc_name_seq {int dummy; } ;
struct subscriber {scalar_t__ port_ref; int /*<<< orphan*/ * lock; int /*<<< orphan*/  subscriber_list; int /*<<< orphan*/  subscription_list; } ;
struct sk_buff {int dummy; } ;
struct iovec {int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_6__ {TYPE_1__ publ; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  subscriber_list; int /*<<< orphan*/  user_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct subscriber*) ; 
 struct subscriber* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subscr_conn_msg_event (struct subscriber*,scalar_t__,struct sk_buff**,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  subscr_conn_shutdown_event ; 
 int /*<<< orphan*/  tipc_connect2port (scalar_t__,struct tipc_portid const*) ; 
 int /*<<< orphan*/  tipc_createport (int /*<<< orphan*/ ,struct subscriber*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct subscriber*,scalar_t__,struct sk_buff**,int /*<<< orphan*/  const*,scalar_t__),int /*<<< orphan*/ *,scalar_t__*) ; 
 TYPE_3__* tipc_port_lock (scalar_t__) ; 
 int /*<<< orphan*/  tipc_send (scalar_t__,int,struct iovec*) ; 
 TYPE_2__ topsrv ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void subscr_named_msg_event(void *usr_handle,
				   u32 port_ref,
				   struct sk_buff **buf,
				   const unchar *data,
				   u32 size,
				   u32 importance,
				   struct tipc_portid const *orig,
				   struct tipc_name_seq const *dest)
{
	static struct iovec msg_sect = {NULL, 0};

	struct subscriber *subscriber;
	u32 server_port_ref;

	/* Create subscriber object */

	subscriber = kzalloc(sizeof(struct subscriber), GFP_ATOMIC);
	if (subscriber == NULL) {
		warn("Subscriber rejected, no memory\n");
		return;
	}
	INIT_LIST_HEAD(&subscriber->subscription_list);
	INIT_LIST_HEAD(&subscriber->subscriber_list);

	/* Create server port & establish connection to subscriber */

	tipc_createport(topsrv.user_ref,
			subscriber,
			importance,
			NULL,
			NULL,
			subscr_conn_shutdown_event,
			NULL,
			NULL,
			subscr_conn_msg_event,
			NULL,
			&subscriber->port_ref);
	if (subscriber->port_ref == 0) {
		warn("Subscriber rejected, unable to create port\n");
		kfree(subscriber);
		return;
	}
	tipc_connect2port(subscriber->port_ref, orig);

	/* Lock server port (& save lock address for future use) */

	subscriber->lock = tipc_port_lock(subscriber->port_ref)->publ.lock;

	/* Add subscriber to topology server's subscriber list */

	spin_lock_bh(&topsrv.lock);
	list_add(&subscriber->subscriber_list, &topsrv.subscriber_list);
	spin_unlock_bh(&topsrv.lock);

	/* Unlock server port */

	server_port_ref = subscriber->port_ref;
	spin_unlock_bh(subscriber->lock);

	/* Send an ACK- to complete connection handshaking */

	tipc_send(server_port_ref, 1, &msg_sect);

	/* Handle optional subscription request */

	if (size != 0) {
		subscr_conn_msg_event(subscriber, server_port_ref,
				      buf, data, size);
	}
}