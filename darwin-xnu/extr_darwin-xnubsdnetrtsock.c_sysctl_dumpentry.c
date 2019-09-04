#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct walkarg {scalar_t__ w_op; int w_arg; int /*<<< orphan*/ * w_req; int /*<<< orphan*/ * w_tmem; } ;
struct rtentry {int rt_flags; TYPE_1__* rt_parent; int /*<<< orphan*/  rt_refcnt; TYPE_2__* rt_ifp; int /*<<< orphan*/  rt_use; int /*<<< orphan*/  rt_genmask; int /*<<< orphan*/  rt_gateway; } ;
struct rt_msghdr2 {int rtm_flags; int /*<<< orphan*/  rtm_addrs; scalar_t__ rtm_reserved; scalar_t__ rtm_parentflags; int /*<<< orphan*/  rtm_refcnt; int /*<<< orphan*/  rtm_index; int /*<<< orphan*/  rtm_rmx; int /*<<< orphan*/  rtm_use; } ;
struct rt_msghdr {int rtm_flags; int /*<<< orphan*/  rtm_addrs; scalar_t__ rtm_errno; scalar_t__ rtm_seq; scalar_t__ rtm_pid; int /*<<< orphan*/  rtm_index; int /*<<< orphan*/  rtm_rmx; int /*<<< orphan*/  rtm_use; } ;
struct rt_addrinfo {int /*<<< orphan*/  rti_addrs; int /*<<< orphan*/ * rti_info; } ;
struct radix_node {int dummy; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  if_index; } ;
struct TYPE_3__ {scalar_t__ rt_flags; } ;

/* Variables and functions */
 scalar_t__ NET_RT_DUMP2 ; 
 scalar_t__ NET_RT_FLAGS ; 
 scalar_t__ NET_RT_FLAGS_PRIV ; 
 int /*<<< orphan*/  ROUTE_OP_READ ; 
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 size_t RTAX_GENMASK ; 
 size_t RTAX_NETMASK ; 
 int RTF_LLINFO ; 
 int /*<<< orphan*/  RTM_GET ; 
 int /*<<< orphan*/  RTM_GET2 ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int SYSCTL_OUT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 TYPE_2__* lo_ifp ; 
 scalar_t__ route_op_entitlement_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_getmetrics (struct rtentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rt_mask (struct rtentry*) ; 
 int rt_msg2 (int /*<<< orphan*/ ,struct rt_addrinfo*,int /*<<< orphan*/ *,struct walkarg*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sysctl_dumpentry(struct radix_node *rn, void *vw)
{
	struct walkarg *w = vw;
	struct rtentry *rt = (struct rtentry *)rn;
	int error = 0, size;
	struct rt_addrinfo info;
	kauth_cred_t cred;
	kauth_cred_t *credp;

	cred = kauth_cred_proc_ref(current_proc());
	credp = &cred;

	RT_LOCK(rt);
	if ((w->w_op == NET_RT_FLAGS || w->w_op == NET_RT_FLAGS_PRIV) &&
	    !(rt->rt_flags & w->w_arg))
		goto done;

	/*
	 * If the matching route has RTF_LLINFO set, then we can skip scrubbing the MAC
	 * only if the outgoing interface is not loopback and the process has entitlement
	 * for neighbor cache read.
	 */
	if (w->w_op == NET_RT_FLAGS_PRIV && (rt->rt_flags & RTF_LLINFO)) {
		if (rt->rt_ifp != lo_ifp &&
		    (route_op_entitlement_check(NULL, cred, ROUTE_OP_READ, TRUE) == 0)) {
			credp = NULL;
		}
	}

	bzero((caddr_t)&info, sizeof (info));
	info.rti_info[RTAX_DST] = rt_key(rt);
	info.rti_info[RTAX_GATEWAY] = rt->rt_gateway;
	info.rti_info[RTAX_NETMASK] = rt_mask(rt);
	info.rti_info[RTAX_GENMASK] = rt->rt_genmask;

	if (w->w_op != NET_RT_DUMP2) {
		size = rt_msg2(RTM_GET, &info, NULL, w, credp);
		if (w->w_req != NULL && w->w_tmem != NULL) {
			struct rt_msghdr *rtm =
			    (struct rt_msghdr *)(void *)w->w_tmem;

			rtm->rtm_flags = rt->rt_flags;
			rtm->rtm_use = rt->rt_use;
			rt_getmetrics(rt, &rtm->rtm_rmx);
			rtm->rtm_index = rt->rt_ifp->if_index;
			rtm->rtm_pid = 0;
			rtm->rtm_seq = 0;
			rtm->rtm_errno = 0;
			rtm->rtm_addrs = info.rti_addrs;
			error = SYSCTL_OUT(w->w_req, (caddr_t)rtm, size);
		}
	} else {
		size = rt_msg2(RTM_GET2, &info, NULL, w, credp);
		if (w->w_req != NULL && w->w_tmem != NULL) {
			struct rt_msghdr2 *rtm =
			    (struct rt_msghdr2 *)(void *)w->w_tmem;

			rtm->rtm_flags = rt->rt_flags;
			rtm->rtm_use = rt->rt_use;
			rt_getmetrics(rt, &rtm->rtm_rmx);
			rtm->rtm_index = rt->rt_ifp->if_index;
			rtm->rtm_refcnt = rt->rt_refcnt;
			if (rt->rt_parent)
				rtm->rtm_parentflags = rt->rt_parent->rt_flags;
			else
				rtm->rtm_parentflags = 0;
			rtm->rtm_reserved = 0;
			rtm->rtm_addrs = info.rti_addrs;
			error = SYSCTL_OUT(w->w_req, (caddr_t)rtm, size);
		}
	}

done:
	RT_UNLOCK(rt);
	kauth_cred_unref(&cred);
	return (error);
}