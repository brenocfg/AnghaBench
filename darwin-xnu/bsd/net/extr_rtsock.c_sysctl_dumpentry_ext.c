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
struct walkarg {scalar_t__ w_op; int w_arg; int /*<<< orphan*/ * w_req; int /*<<< orphan*/ * w_tmem; } ;
struct rtentry {int rt_flags; int /*<<< orphan*/  (* rt_llinfo_get_ri ) (struct rtentry*,struct rt_addrinfo*) ;TYPE_1__* rt_ifp; int /*<<< orphan*/  rt_use; int /*<<< orphan*/  rt_genmask; int /*<<< orphan*/  rt_gateway; } ;
struct rt_addrinfo {int /*<<< orphan*/  ri_npm; int /*<<< orphan*/  ri_lqm; int /*<<< orphan*/  ri_rssi; int /*<<< orphan*/  rti_addrs; int /*<<< orphan*/ * rti_info; } ;
struct rt_msghdr_ext {int rtm_flags; struct rt_addrinfo rtm_ri; int /*<<< orphan*/  rtm_addrs; scalar_t__ rtm_errno; scalar_t__ rtm_seq; scalar_t__ rtm_pid; int /*<<< orphan*/  rtm_index; int /*<<< orphan*/  rtm_rmx; int /*<<< orphan*/  rtm_use; } ;
struct radix_node {int dummy; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNET_LQM_THRESH_OFF ; 
 int /*<<< orphan*/  IFNET_NPM_THRESH_UNKNOWN ; 
 int /*<<< orphan*/  IFNET_RSSI_UNKNOWN ; 
 scalar_t__ NET_RT_DUMPX_FLAGS ; 
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 size_t RTAX_GENMASK ; 
 size_t RTAX_NETMASK ; 
 int /*<<< orphan*/  RTM_GET_EXT ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int SYSCTL_OUT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct rt_addrinfo*,int) ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_getmetrics (struct rtentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rt_mask (struct rtentry*) ; 
 int rt_msg2 (int /*<<< orphan*/ ,struct rt_addrinfo*,int /*<<< orphan*/ *,struct walkarg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rtentry*,struct rt_addrinfo*) ; 

__attribute__((used)) static int
sysctl_dumpentry_ext(struct radix_node *rn, void *vw)
{
	struct walkarg *w = vw;
	struct rtentry *rt = (struct rtentry *)rn;
	int error = 0, size;
	struct rt_addrinfo info;
	kauth_cred_t cred;

	cred = kauth_cred_proc_ref(current_proc());

	RT_LOCK(rt);
	if (w->w_op == NET_RT_DUMPX_FLAGS && !(rt->rt_flags & w->w_arg))
		goto done;
	bzero(&info, sizeof (info));
	info.rti_info[RTAX_DST] = rt_key(rt);
	info.rti_info[RTAX_GATEWAY] = rt->rt_gateway;
	info.rti_info[RTAX_NETMASK] = rt_mask(rt);
	info.rti_info[RTAX_GENMASK] = rt->rt_genmask;

	size = rt_msg2(RTM_GET_EXT, &info, NULL, w, &cred);
	if (w->w_req != NULL && w->w_tmem != NULL) {
		struct rt_msghdr_ext *ertm =
		    (struct rt_msghdr_ext *)(void *)w->w_tmem;

		ertm->rtm_flags = rt->rt_flags;
		ertm->rtm_use = rt->rt_use;
		rt_getmetrics(rt, &ertm->rtm_rmx);
		ertm->rtm_index = rt->rt_ifp->if_index;
		ertm->rtm_pid = 0;
		ertm->rtm_seq = 0;
		ertm->rtm_errno = 0;
		ertm->rtm_addrs = info.rti_addrs;
		if (rt->rt_llinfo_get_ri == NULL) {
			bzero(&ertm->rtm_ri, sizeof (ertm->rtm_ri));
			ertm->rtm_ri.ri_rssi = IFNET_RSSI_UNKNOWN;
			ertm->rtm_ri.ri_lqm = IFNET_LQM_THRESH_OFF;
			ertm->rtm_ri.ri_npm = IFNET_NPM_THRESH_UNKNOWN;
		} else {
			rt->rt_llinfo_get_ri(rt, &ertm->rtm_ri);
		}
		error = SYSCTL_OUT(w->w_req, (caddr_t)ertm, size);
	}

done:
	RT_UNLOCK(rt);
	kauth_cred_unref(&cred);
	return (error);
}