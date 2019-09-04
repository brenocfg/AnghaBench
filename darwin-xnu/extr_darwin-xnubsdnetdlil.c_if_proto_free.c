#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct net_event_data {int dummy; } ;
struct kev_dl_proto_data {int proto_family; scalar_t__ proto_remaining_count; } ;
struct ifnet {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* detached ) (struct ifnet*,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* detached ) (struct ifnet*,int) ;} ;
struct TYPE_6__ {TYPE_2__ v2; TYPE_1__ v1; } ;
struct if_proto {int protocol_family; scalar_t__ proto_kpi; TYPE_3__ kpi; int /*<<< orphan*/  detached; int /*<<< orphan*/  refcount; struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  KEV_DL_PROTO_DETACHED ; 
 int /*<<< orphan*/  KEV_DL_SUBCLASS ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int atomic_add_32_ov (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dlif_proto_zone ; 
 scalar_t__ dlil_ifp_protolist (struct ifnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlil_post_msg (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_event_data*,int) ; 
 int /*<<< orphan*/  dlil_post_sifflags_msg (struct ifnet*) ; 
 int /*<<< orphan*/  if_rtproto_del (struct ifnet*,int) ; 
 int /*<<< orphan*/  ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_set_flags (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kProtoKPI_v1 ; 
 scalar_t__ kProtoKPI_v2 ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,int) ; 
 int /*<<< orphan*/  stub2 (struct ifnet*,int) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct if_proto*) ; 

__attribute__((used)) static void
if_proto_free(struct if_proto *proto)
{
	u_int32_t oldval;
	struct ifnet *ifp = proto->ifp;
	u_int32_t proto_family = proto->protocol_family;
	struct kev_dl_proto_data ev_pr_data;

	oldval = atomic_add_32_ov(&proto->refcount, -1);
	if (oldval > 1)
		return;

	/* No more reference on this, protocol must have been detached */
	VERIFY(proto->detached);

	if (proto->proto_kpi == kProtoKPI_v1) {
		if (proto->kpi.v1.detached)
			proto->kpi.v1.detached(ifp, proto->protocol_family);
	}
	if (proto->proto_kpi == kProtoKPI_v2) {
		if (proto->kpi.v2.detached)
			proto->kpi.v2.detached(ifp, proto->protocol_family);
	}

	/*
	 * Cleanup routes that may still be in the routing table for that
	 * interface/protocol pair.
	 */
	if_rtproto_del(ifp, proto_family);

	/*
	 * The reserved field carries the number of protocol still attached
	 * (subject to change)
	 */
	ifnet_lock_shared(ifp);
	ev_pr_data.proto_family = proto_family;
	ev_pr_data.proto_remaining_count = dlil_ifp_protolist(ifp, NULL, 0);
	ifnet_lock_done(ifp);

	dlil_post_msg(ifp, KEV_DL_SUBCLASS, KEV_DL_PROTO_DETACHED,
	    (struct net_event_data *)&ev_pr_data,
	    sizeof (struct kev_dl_proto_data));

	if (ev_pr_data.proto_remaining_count == 0) {
		/*
		 * The protocol count has gone to zero, mark the interface down.
		 * This used to be done by configd.KernelEventMonitor, but that
		 * is inherently prone to races (rdar://problem/30810208).
		 */
		(void) ifnet_set_flags(ifp, 0, IFF_UP);
		(void) ifnet_ioctl(ifp, 0, SIOCSIFFLAGS, NULL);
		dlil_post_sifflags_msg(ifp);
	}

	zfree(dlif_proto_zone, proto);
}