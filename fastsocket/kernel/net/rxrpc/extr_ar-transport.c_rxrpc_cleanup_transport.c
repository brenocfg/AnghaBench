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
struct rxrpc_transport {int /*<<< orphan*/  peer; int /*<<< orphan*/  local; int /*<<< orphan*/  error_queue; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  _net (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rxrpc_transport*) ; 
 int /*<<< orphan*/  rxrpc_purge_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_put_local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_put_peer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_cleanup_transport(struct rxrpc_transport *trans)
{
	_net("DESTROY TRANS %d", trans->debug_id);

	rxrpc_purge_queue(&trans->error_queue);

	rxrpc_put_local(trans->local);
	rxrpc_put_peer(trans->peer);
	kfree(trans);
}