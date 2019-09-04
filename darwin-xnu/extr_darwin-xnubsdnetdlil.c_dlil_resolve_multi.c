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
struct sockaddr_dl {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct ifnet {scalar_t__ (* if_check_multi ) (struct ifnet*,struct sockaddr const*) ;} ;
struct TYPE_5__ {scalar_t__ (* resolve_multi ) (struct ifnet*,struct sockaddr const*,struct sockaddr_dl*,size_t) ;} ;
struct TYPE_4__ {scalar_t__ (* resolve_multi ) (struct ifnet*,struct sockaddr const*,struct sockaddr_dl*,size_t) ;} ;
struct TYPE_6__ {TYPE_2__ v2; TYPE_1__ v1; } ;
struct if_proto {scalar_t__ proto_kpi; TYPE_3__ kpi; } ;
typedef  scalar_t__ (* proto_media_resolve_multi ) (struct ifnet*,struct sockaddr const*,struct sockaddr_dl*,size_t) ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 scalar_t__ EOPNOTSUPP ; 
 int /*<<< orphan*/  bzero (struct sockaddr*,size_t) ; 
 struct if_proto* find_attached_proto (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_proto_free (struct if_proto*) ; 
 int /*<<< orphan*/  ifnet_decr_iorefcnt (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_is_attached (struct ifnet*,int) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 
 scalar_t__ kProtoKPI_v1 ; 
 scalar_t__ stub1 (struct ifnet*,struct sockaddr const*) ; 

errno_t
dlil_resolve_multi(struct ifnet *ifp, const struct sockaddr *proto_addr,
    struct sockaddr *ll_addr, size_t ll_len)
{
	errno_t	result = EOPNOTSUPP;
	struct if_proto *proto;
	const struct sockaddr *verify;
	proto_media_resolve_multi resolvep;

	if (!ifnet_is_attached(ifp, 1))
		return (result);

	bzero(ll_addr, ll_len);

	/* Call the protocol first; callee holds a proto refcnt upon success */
	ifnet_lock_shared(ifp);
	proto = find_attached_proto(ifp, proto_addr->sa_family);
	ifnet_lock_done(ifp);
	if (proto != NULL) {
		resolvep = (proto->proto_kpi == kProtoKPI_v1 ?
		    proto->kpi.v1.resolve_multi : proto->kpi.v2.resolve_multi);
		if (resolvep != NULL)
			result = resolvep(ifp, proto_addr,
			    (struct sockaddr_dl *)(void *)ll_addr, ll_len);
		if_proto_free(proto);
	}

	/* Let the interface verify the multicast address */
	if ((result == EOPNOTSUPP || result == 0) && ifp->if_check_multi) {
		if (result == 0)
			verify = ll_addr;
		else
			verify = proto_addr;
		result = ifp->if_check_multi(ifp, verify);
	}

	ifnet_decr_iorefcnt(ifp);
	return (result);
}