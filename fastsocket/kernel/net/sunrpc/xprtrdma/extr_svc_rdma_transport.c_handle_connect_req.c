#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  xpt_flags; int /*<<< orphan*/  xpt_server; } ;
struct svcxprt_rdma {size_t sc_ord; TYPE_3__ sc_xprt; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_accept_q; struct rdma_cm_id* sc_cm_id; } ;
struct sockaddr {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  src_addr; int /*<<< orphan*/  dst_addr; } ;
struct TYPE_7__ {TYPE_1__ addr; } ;
struct rdma_cm_id {TYPE_2__ route; struct svcxprt_rdma* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPT_CONN ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct svcxprt_rdma* rdma_create_xprt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_addr_len (struct sockaddr*) ; 
 int /*<<< orphan*/  svc_xprt_enqueue (TYPE_3__*) ; 
 int /*<<< orphan*/  svc_xprt_set_local (TYPE_3__*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_xprt_set_remote (TYPE_3__*,struct sockaddr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_connect_req(struct rdma_cm_id *new_cma_id, size_t client_ird)
{
	struct svcxprt_rdma *listen_xprt = new_cma_id->context;
	struct svcxprt_rdma *newxprt;
	struct sockaddr *sa;

	/* Create a new transport */
	newxprt = rdma_create_xprt(listen_xprt->sc_xprt.xpt_server, 0);
	if (!newxprt) {
		dprintk("svcrdma: failed to create new transport\n");
		return;
	}
	newxprt->sc_cm_id = new_cma_id;
	new_cma_id->context = newxprt;
	dprintk("svcrdma: Creating newxprt=%p, cm_id=%p, listenxprt=%p\n",
		newxprt, newxprt->sc_cm_id, listen_xprt);

	/* Save client advertised inbound read limit for use later in accept. */
	newxprt->sc_ord = client_ird;

	/* Set the local and remote addresses in the transport */
	sa = (struct sockaddr *)&newxprt->sc_cm_id->route.addr.dst_addr;
	svc_xprt_set_remote(&newxprt->sc_xprt, sa, svc_addr_len(sa));
	sa = (struct sockaddr *)&newxprt->sc_cm_id->route.addr.src_addr;
	svc_xprt_set_local(&newxprt->sc_xprt, sa, svc_addr_len(sa));

	/*
	 * Enqueue the new transport on the accept queue of the listening
	 * transport
	 */
	spin_lock_bh(&listen_xprt->sc_lock);
	list_add_tail(&newxprt->sc_accept_q, &listen_xprt->sc_accept_q);
	spin_unlock_bh(&listen_xprt->sc_lock);

	/*
	 * Can't use svc_xprt_received here because we are not on a
	 * rqstp thread
	*/
	set_bit(XPT_CONN, &listen_xprt->sc_xprt.xpt_flags);
	svc_xprt_enqueue(&listen_xprt->sc_xprt);
}