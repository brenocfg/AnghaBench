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
struct afs_wait_mode {int dummy; } ;
struct afs_server {size_t cb_break_tail; int /*<<< orphan*/  addr; int /*<<< orphan*/  cb_break_waitq; struct afs_callback* cb_break; int /*<<< orphan*/  cb_break_n; int /*<<< orphan*/  cb_break_head; } ;
struct TYPE_2__ {size_t vid; size_t vnode; size_t unique; } ;
struct afs_callback {size_t version; size_t expiry; size_t type; TYPE_1__ fid; } ;
struct afs_call {int /*<<< orphan*/ * request; int /*<<< orphan*/  port; int /*<<< orphan*/  service_id; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 size_t AFSCBMAX ; 
 int /*<<< orphan*/  AFS_FS_PORT ; 
 int ARRAY_SIZE (struct afs_callback*) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t CIRC_CNT (int /*<<< orphan*/ ,size_t,int) ; 
 int ENOMEM ; 
 size_t FSGIVEUPCALLBACKS ; 
 int /*<<< orphan*/  FS_SERVICE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _debug (char*,size_t) ; 
 int /*<<< orphan*/  _enter (char*,size_t) ; 
 int /*<<< orphan*/  afs_RXFSGiveUpCallBacks ; 
 struct afs_call* afs_alloc_flat_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ,struct afs_wait_mode const*) ; 
 int /*<<< orphan*/  atomic_sub (size_t,int /*<<< orphan*/ *) ; 
 void* htonl (size_t) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  wake_up_nr (int /*<<< orphan*/ *,size_t) ; 

int afs_fs_give_up_callbacks(struct afs_server *server,
			     const struct afs_wait_mode *wait_mode)
{
	struct afs_call *call;
	size_t ncallbacks;
	__be32 *bp, *tp;
	int loop;

	ncallbacks = CIRC_CNT(server->cb_break_head, server->cb_break_tail,
			      ARRAY_SIZE(server->cb_break));

	_enter("{%zu},", ncallbacks);

	if (ncallbacks == 0)
		return 0;
	if (ncallbacks > AFSCBMAX)
		ncallbacks = AFSCBMAX;

	_debug("break %zu callbacks", ncallbacks);

	call = afs_alloc_flat_call(&afs_RXFSGiveUpCallBacks,
				   12 + ncallbacks * 6 * 4, 0);
	if (!call)
		return -ENOMEM;

	call->service_id = FS_SERVICE;
	call->port = htons(AFS_FS_PORT);

	/* marshall the parameters */
	bp = call->request;
	tp = bp + 2 + ncallbacks * 3;
	*bp++ = htonl(FSGIVEUPCALLBACKS);
	*bp++ = htonl(ncallbacks);
	*tp++ = htonl(ncallbacks);

	atomic_sub(ncallbacks, &server->cb_break_n);
	for (loop = ncallbacks; loop > 0; loop--) {
		struct afs_callback *cb =
			&server->cb_break[server->cb_break_tail];

		*bp++ = htonl(cb->fid.vid);
		*bp++ = htonl(cb->fid.vnode);
		*bp++ = htonl(cb->fid.unique);
		*tp++ = htonl(cb->version);
		*tp++ = htonl(cb->expiry);
		*tp++ = htonl(cb->type);
		smp_mb();
		server->cb_break_tail =
			(server->cb_break_tail + 1) &
			(ARRAY_SIZE(server->cb_break) - 1);
	}

	ASSERT(ncallbacks > 0);
	wake_up_nr(&server->cb_break_waitq, ncallbacks);

	return afs_make_call(&server->addr, call, GFP_NOFS, wait_mode);
}