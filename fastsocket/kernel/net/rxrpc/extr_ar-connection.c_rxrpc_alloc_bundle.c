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
struct rxrpc_conn_bundle {int /*<<< orphan*/  usage; int /*<<< orphan*/  chanwait; int /*<<< orphan*/  busy_conns; int /*<<< orphan*/  avail_conns; int /*<<< orphan*/  unused_conns; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_conn_bundle*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct rxrpc_conn_bundle* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rxrpc_conn_bundle *rxrpc_alloc_bundle(gfp_t gfp)
{
	struct rxrpc_conn_bundle *bundle;

	_enter("");

	bundle = kzalloc(sizeof(struct rxrpc_conn_bundle), gfp);
	if (bundle) {
		INIT_LIST_HEAD(&bundle->unused_conns);
		INIT_LIST_HEAD(&bundle->avail_conns);
		INIT_LIST_HEAD(&bundle->busy_conns);
		init_waitqueue_head(&bundle->chanwait);
		atomic_set(&bundle->usage, 1);
	}

	_leave(" = %p", bundle);
	return bundle;
}