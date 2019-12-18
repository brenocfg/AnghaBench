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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u_int32_t ;
struct net_event_data {int dummy; } ;
struct kev_dl_proto_data {int /*<<< orphan*/  proto_remaining_count; int /*<<< orphan*/  proto_family; } ;
struct ifnet_demux_desc {int dummy; } ;
struct ifnet {int (* if_add_proto ) (struct ifnet*,int /*<<< orphan*/ ,struct ifnet_demux_desc const*,size_t) ;int /*<<< orphan*/ * if_proto_hash; } ;
struct if_proto {int /*<<< orphan*/  protocol_family; struct ifnet* ifp; } ;
typedef  int errno_t ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  KEV_DL_PROTO_ATTACHED ; 
 int /*<<< orphan*/  KEV_DL_SUBCLASS ; 
 struct if_proto* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_AFTER (struct if_proto*,struct if_proto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct if_proto*,int /*<<< orphan*/ ) ; 
 struct if_proto* SLIST_NEXT (struct if_proto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlil_ifp_protolist (struct ifnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlil_post_msg (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_event_data*,int) ; 
 struct if_proto* find_attached_proto (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_proto_free (struct if_proto*) ; 
 int /*<<< orphan*/  if_proto_ref (struct if_proto*) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int /*<<< orphan*/  next_hash ; 
 size_t proto_hash_value (int /*<<< orphan*/ ) ; 
 int stub1 (struct ifnet*,int /*<<< orphan*/ ,struct ifnet_demux_desc const*,size_t) ; 

__attribute__((used)) static errno_t
dlil_attach_protocol_internal(struct if_proto *proto,
    const struct ifnet_demux_desc *demux_list, u_int32_t demux_count,
    uint32_t * proto_count)
{
	struct kev_dl_proto_data ev_pr_data;
	struct ifnet *ifp = proto->ifp;
	int retval = 0;
	u_int32_t hash_value = proto_hash_value(proto->protocol_family);
	struct if_proto *prev_proto;
	struct if_proto *_proto;

	/* callee holds a proto refcnt upon success */
	ifnet_lock_exclusive(ifp);
	_proto = find_attached_proto(ifp, proto->protocol_family);
	if (_proto != NULL) {
		ifnet_lock_done(ifp);
		if_proto_free(_proto);
		return (EEXIST);
	}

	/*
	 * Call family module add_proto routine so it can refine the
	 * demux descriptors as it wishes.
	 */
	retval = ifp->if_add_proto(ifp, proto->protocol_family, demux_list,
	    demux_count);
	if (retval) {
		ifnet_lock_done(ifp);
		return (retval);
	}

	/*
	 * Insert the protocol in the hash
	 */
	prev_proto = SLIST_FIRST(&ifp->if_proto_hash[hash_value]);
	while (prev_proto != NULL && SLIST_NEXT(prev_proto, next_hash) != NULL)
		prev_proto = SLIST_NEXT(prev_proto, next_hash);
	if (prev_proto)
		SLIST_INSERT_AFTER(prev_proto, proto, next_hash);
	else
		SLIST_INSERT_HEAD(&ifp->if_proto_hash[hash_value],
		    proto, next_hash);

	/* hold a proto refcnt for attach */
	if_proto_ref(proto);

	/*
	 * The reserved field carries the number of protocol still attached
	 * (subject to change)
	 */
	ev_pr_data.proto_family = proto->protocol_family;
	ev_pr_data.proto_remaining_count = dlil_ifp_protolist(ifp, NULL, 0);

	ifnet_lock_done(ifp);

	dlil_post_msg(ifp, KEV_DL_SUBCLASS, KEV_DL_PROTO_ATTACHED,
	    (struct net_event_data *)&ev_pr_data,
	    sizeof (struct kev_dl_proto_data));
	if (proto_count != NULL) {
		*proto_count = ev_pr_data.proto_remaining_count;
	}
	return (retval);
}