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
struct rxrpc_header {int dummy; } ;
struct rxrpc_connection {int size_align; int header_size; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  avail_calls; int /*<<< orphan*/  usage; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  calls; int /*<<< orphan*/  bundle_link; int /*<<< orphan*/  processor; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  RXRPC_MAXCALLS ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct rxrpc_connection* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_debug_id ; 
 int /*<<< orphan*/  rxrpc_process_connection ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rxrpc_connection *rxrpc_alloc_connection(gfp_t gfp)
{
	struct rxrpc_connection *conn;

	_enter("");

	conn = kzalloc(sizeof(struct rxrpc_connection), gfp);
	if (conn) {
		INIT_WORK(&conn->processor, &rxrpc_process_connection);
		INIT_LIST_HEAD(&conn->bundle_link);
		conn->calls = RB_ROOT;
		skb_queue_head_init(&conn->rx_queue);
		rwlock_init(&conn->lock);
		spin_lock_init(&conn->state_lock);
		atomic_set(&conn->usage, 1);
		conn->debug_id = atomic_inc_return(&rxrpc_debug_id);
		conn->avail_calls = RXRPC_MAXCALLS;
		conn->size_align = 4;
		conn->header_size = sizeof(struct rxrpc_header);
	}

	_leave(" = %p{%d}", conn, conn ? conn->debug_id : 0);
	return conn;
}