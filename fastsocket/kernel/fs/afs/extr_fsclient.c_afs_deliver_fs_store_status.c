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
struct sk_buff {int dummy; } ;
struct afs_vnode {int /*<<< orphan*/  status; } ;
struct afs_call {scalar_t__ reply_size; scalar_t__ reply_max; scalar_t__ operation_ID; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  store_version; struct afs_vnode* reply; } ;
typedef  int /*<<< orphan*/  afs_dataversion_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EBADMSG ; 
 scalar_t__ FSSTOREDATA ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  afs_transfer_reply (struct afs_call*,struct sk_buff*) ; 
 int /*<<< orphan*/  xdr_decode_AFSFetchStatus (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,struct afs_vnode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_deliver_fs_store_status(struct afs_call *call,
				       struct sk_buff *skb, bool last)
{
	afs_dataversion_t *store_version;
	struct afs_vnode *vnode = call->reply;
	const __be32 *bp;

	_enter(",,%u", last);

	afs_transfer_reply(call, skb);
	if (!last) {
		_leave(" = 0 [more]");
		return 0;
	}

	if (call->reply_size != call->reply_max) {
		_leave(" = -EBADMSG [%u != %u]",
		       call->reply_size, call->reply_max);
		return -EBADMSG;
	}

	/* unmarshall the reply once we've received all of it */
	store_version = NULL;
	if (call->operation_ID == FSSTOREDATA)
		store_version = &call->store_version;

	bp = call->buffer;
	xdr_decode_AFSFetchStatus(&bp, &vnode->status, vnode, store_version);
	/* xdr_decode_AFSVolSync(&bp, call->replyX); */

	_leave(" = 0 [done]");
	return 0;
}