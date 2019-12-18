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
struct rxrpc_transport {int /*<<< orphan*/  error_handler; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  usage; int /*<<< orphan*/  conn_lock; int /*<<< orphan*/  client_lock; int /*<<< orphan*/  error_queue; void* server_conns; void* client_conns; void* bundles; int /*<<< orphan*/  link; struct rxrpc_peer* peer; struct rxrpc_local* local; } ;
struct TYPE_3__ {scalar_t__ family; } ;
struct TYPE_4__ {int transport_type; TYPE_1__ transport; } ;
struct rxrpc_peer {TYPE_2__ srx; } ;
struct rxrpc_local {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* RB_ROOT ; 
#define  SOCK_DGRAM 128 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_transport*) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct rxrpc_transport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_UDP_error_handler ; 
 int /*<<< orphan*/  rxrpc_debug_id ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rxrpc_transport *rxrpc_alloc_transport(struct rxrpc_local *local,
						     struct rxrpc_peer *peer,
						     gfp_t gfp)
{
	struct rxrpc_transport *trans;

	_enter("");

	trans = kzalloc(sizeof(struct rxrpc_transport), gfp);
	if (trans) {
		trans->local = local;
		trans->peer = peer;
		INIT_LIST_HEAD(&trans->link);
		trans->bundles = RB_ROOT;
		trans->client_conns = RB_ROOT;
		trans->server_conns = RB_ROOT;
		skb_queue_head_init(&trans->error_queue);
		spin_lock_init(&trans->client_lock);
		rwlock_init(&trans->conn_lock);
		atomic_set(&trans->usage, 1);
		trans->debug_id = atomic_inc_return(&rxrpc_debug_id);

		if (peer->srx.transport.family == AF_INET) {
			switch (peer->srx.transport_type) {
			case SOCK_DGRAM:
				INIT_WORK(&trans->error_handler,
					  rxrpc_UDP_error_handler);
				break;
			default:
				BUG();
				break;
			}
		} else {
			BUG();
		}
	}

	_leave(" = %p", trans);
	return trans;
}