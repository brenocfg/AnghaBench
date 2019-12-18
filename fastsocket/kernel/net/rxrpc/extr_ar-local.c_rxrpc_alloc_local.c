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
struct sockaddr_rxrpc {int dummy; } ;
struct rxrpc_local {int /*<<< orphan*/  srx; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  usage; int /*<<< orphan*/  services_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  reject_queue; int /*<<< orphan*/  accept_queue; int /*<<< orphan*/  defrag_sem; int /*<<< orphan*/  link; int /*<<< orphan*/  services; int /*<<< orphan*/  rejecter; int /*<<< orphan*/  acceptor; int /*<<< orphan*/  destroyer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_local*) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct rxrpc_local* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_rxrpc*,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_accept_incoming_calls ; 
 int /*<<< orphan*/  rxrpc_debug_id ; 
 int /*<<< orphan*/  rxrpc_destroy_local ; 
 int /*<<< orphan*/  rxrpc_reject_packets ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
struct rxrpc_local *rxrpc_alloc_local(struct sockaddr_rxrpc *srx)
{
	struct rxrpc_local *local;

	local = kzalloc(sizeof(struct rxrpc_local), GFP_KERNEL);
	if (local) {
		INIT_WORK(&local->destroyer, &rxrpc_destroy_local);
		INIT_WORK(&local->acceptor, &rxrpc_accept_incoming_calls);
		INIT_WORK(&local->rejecter, &rxrpc_reject_packets);
		INIT_LIST_HEAD(&local->services);
		INIT_LIST_HEAD(&local->link);
		init_rwsem(&local->defrag_sem);
		skb_queue_head_init(&local->accept_queue);
		skb_queue_head_init(&local->reject_queue);
		spin_lock_init(&local->lock);
		rwlock_init(&local->services_lock);
		atomic_set(&local->usage, 1);
		local->debug_id = atomic_inc_return(&rxrpc_debug_id);
		memcpy(&local->srx, srx, sizeof(*srx));
	}

	_leave(" = %p", local);
	return local;
}