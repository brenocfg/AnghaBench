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
struct rtentry {struct llinfo_arp* rt_llinfo; } ;
struct llinfo_arp {int /*<<< orphan*/  la_lastused; struct if_llreach* la_llreach; } ;
struct ifnet_llreach_info {int /*<<< orphan*/  iflri_snd_expire; int /*<<< orphan*/  iflri_npm; int /*<<< orphan*/  iflri_lqm; int /*<<< orphan*/  iflri_rssi; } ;
struct if_llreach {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFLR_LOCK (struct if_llreach*) ; 
 int /*<<< orphan*/  IFLR_UNLOCK (struct if_llreach*) ; 
 int /*<<< orphan*/  IFNET_LQM_THRESH_OFF ; 
 int /*<<< orphan*/  IFNET_NPM_THRESH_UNKNOWN ; 
 int /*<<< orphan*/  IFNET_RSSI_UNKNOWN ; 
 int /*<<< orphan*/  bzero (struct ifnet_llreach_info*,int) ; 
 int /*<<< orphan*/  ifnet_llreach_up2upexp (struct if_llreach*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_lr2iflri (struct if_llreach*,struct ifnet_llreach_info*) ; 

__attribute__((used)) static void
arp_llinfo_get_iflri(struct rtentry *rt, struct ifnet_llreach_info *iflri)
{
	struct llinfo_arp *la = rt->rt_llinfo;
	struct if_llreach *lr = la->la_llreach;

	if (lr == NULL) {
		bzero(iflri, sizeof (*iflri));
		iflri->iflri_rssi = IFNET_RSSI_UNKNOWN;
		iflri->iflri_lqm = IFNET_LQM_THRESH_OFF;
		iflri->iflri_npm = IFNET_NPM_THRESH_UNKNOWN;
	} else {
		IFLR_LOCK(lr);
		/* Export to ifnet_llreach_info structure */
		ifnet_lr2iflri(lr, iflri);
		/* Export ARP send expiration (uptime) time */
		iflri->iflri_snd_expire =
		    ifnet_llreach_up2upexp(lr, la->la_lastused);
		IFLR_UNLOCK(lr);
	}
}