#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct UNDReply {int dummy; } ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  TYPE_1__* UNDReplyRef ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  self_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_NONE ; 
 int /*<<< orphan*/  IKO_NULL ; 
 int /*<<< orphan*/  IP_NULL ; 
 int /*<<< orphan*/  IP_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockCompatGroup ; 
 int /*<<< orphan*/  UNDReply_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  UNDReply_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_kobject_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_dealloc_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
UNDReply_deallocate(
	UNDReplyRef		reply)
{
	ipc_port_t port;

	UNDReply_lock(reply);
	port = reply->self_port;
	assert(IP_VALID(port));
	ipc_kobject_set(port, IKO_NULL, IKOT_NONE);
	reply->self_port = IP_NULL;
	UNDReply_unlock(reply);

	ipc_port_dealloc_kernel(port);
	lck_mtx_destroy(&reply->lock, &LockCompatGroup);
	kfree(reply, sizeof(struct UNDReply));
	return;
}