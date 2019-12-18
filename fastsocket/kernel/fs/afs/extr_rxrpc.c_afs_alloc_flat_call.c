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
struct afs_call_type {int /*<<< orphan*/  name; } ;
struct afs_call {size_t request_size; size_t reply_max; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  waitq; void* buffer; void* request; struct afs_call_type const* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _debug (char*,struct afs_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_free_call (struct afs_call*) ; 
 int /*<<< orphan*/  afs_outstanding_calls ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 struct afs_call* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

struct afs_call *afs_alloc_flat_call(const struct afs_call_type *type,
				     size_t request_size, size_t reply_size)
{
	struct afs_call *call;

	call = kzalloc(sizeof(*call), GFP_NOFS);
	if (!call)
		goto nomem_call;

	_debug("CALL %p{%s} [%d]",
	       call, type->name, atomic_read(&afs_outstanding_calls));
	atomic_inc(&afs_outstanding_calls);

	call->type = type;
	call->request_size = request_size;
	call->reply_max = reply_size;

	if (request_size) {
		call->request = kmalloc(request_size, GFP_NOFS);
		if (!call->request)
			goto nomem_free;
	}

	if (reply_size) {
		call->buffer = kmalloc(reply_size, GFP_NOFS);
		if (!call->buffer)
			goto nomem_free;
	}

	init_waitqueue_head(&call->waitq);
	skb_queue_head_init(&call->rx_queue);
	return call;

nomem_free:
	afs_free_call(call);
nomem_call:
	return NULL;
}