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
struct ifnet_llreach_info {int /*<<< orphan*/  iflri_npm; int /*<<< orphan*/  iflri_lqm; int /*<<< orphan*/  iflri_rssi; int /*<<< orphan*/  iflri_addr; int /*<<< orphan*/  iflri_netproto; int /*<<< orphan*/  iflri_curtime; int /*<<< orphan*/  iflri_rcv_expire; int /*<<< orphan*/  iflri_probes; int /*<<< orphan*/  iflri_refcnt; } ;
struct TYPE_2__ {int proto; int /*<<< orphan*/  addr; } ;
struct if_llreach {int /*<<< orphan*/  lr_npm; int /*<<< orphan*/  lr_lqm; int /*<<< orphan*/  lr_rssi; TYPE_1__ lr_key; int /*<<< orphan*/  lr_lastrcvd; int /*<<< orphan*/  lr_probes; int /*<<< orphan*/  lr_reqcnt; } ;

/* Variables and functions */
#define  ETHERTYPE_IP 129 
#define  ETHERTYPE_IPV6 128 
 int /*<<< orphan*/  IFLR_LOCK_ASSERT_HELD (struct if_llreach*) ; 
 int /*<<< orphan*/  IF_LLREACH_MAXLEN ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct ifnet_llreach_info*,int) ; 
 int /*<<< orphan*/  ifnet_llreach_up2upexp (struct if_llreach*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_uptime () ; 

void
ifnet_lr2iflri(struct if_llreach *lr, struct ifnet_llreach_info *iflri)
{
	IFLR_LOCK_ASSERT_HELD(lr);

	bzero(iflri, sizeof (*iflri));
	/*
	 * Note here we return request count, not actual memory refcnt.
	 */
	iflri->iflri_refcnt = lr->lr_reqcnt;
	iflri->iflri_probes = lr->lr_probes;
	iflri->iflri_rcv_expire = ifnet_llreach_up2upexp(lr, lr->lr_lastrcvd);
	iflri->iflri_curtime = net_uptime();
	switch (lr->lr_key.proto) {
	case ETHERTYPE_IP:
		iflri->iflri_netproto = PF_INET;
		break;
	case ETHERTYPE_IPV6:
		iflri->iflri_netproto = PF_INET6;
		break;
	default:
		/*
		 * This shouldn't be possible for the time being,
		 * since link-layer reachability records are only
		 * kept for ARP and ND6.
		 */
		iflri->iflri_netproto = PF_UNSPEC;
		break;
	}
	bcopy(&lr->lr_key.addr, &iflri->iflri_addr, IF_LLREACH_MAXLEN);
	iflri->iflri_rssi = lr->lr_rssi;
	iflri->iflri_lqm = lr->lr_lqm;
	iflri->iflri_npm = lr->lr_npm;
}