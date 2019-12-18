#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  sa_data; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; TYPE_1__ ap_addr; scalar_t__ name; } ;
struct iwreq {TYPE_2__ u; } ;
struct ifreq {int dummy; } ;
struct hostap_interface {TYPE_3__* local; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; TYPE_9__* ap; } ;
typedef  TYPE_3__ local_info_t ;
struct TYPE_13__ {int /*<<< orphan*/  mac_restrictions; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  PRISM2_IOCTL_ADDMAC 139 
#define  PRISM2_IOCTL_DELMAC 138 
#define  PRISM2_IOCTL_DOWNLOAD 137 
#define  PRISM2_IOCTL_HOSTAPD 136 
#define  PRISM2_IOCTL_INQUIRE 135 
#define  PRISM2_IOCTL_KICKMAC 134 
#define  PRISM2_IOCTL_MACCMD 133 
#define  PRISM2_IOCTL_MONITOR 132 
#define  PRISM2_IOCTL_RESET 131 
#define  PRISM2_IOCTL_SET_RID_WORD 130 
#define  PRISM2_IOCTL_WDS_ADD 129 
#define  PRISM2_IOCTL_WDS_DEL 128 
 int ap_control_add_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ap_control_del_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ap_control_kick_mac (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ap_mac_cmd_ioctl (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int prism2_ioctl_priv_download (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int prism2_ioctl_priv_hostapd (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int prism2_ioctl_priv_inquire (struct net_device*,int*) ; 
 int prism2_ioctl_priv_monitor (struct net_device*,int*) ; 
 int prism2_ioctl_priv_reset (struct net_device*,int*) ; 
 int prism2_ioctl_priv_set_rid_word (struct net_device*,int*) ; 
 int prism2_wds_add (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int prism2_wds_del (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int hostap_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct iwreq *wrq = (struct iwreq *) ifr;
	struct hostap_interface *iface;
	local_info_t *local;
	int ret = 0;

	iface = netdev_priv(dev);
	local = iface->local;

	switch (cmd) {
		/* Private ioctls (iwpriv) that have not yet been converted
		 * into new wireless extensions API */

	case PRISM2_IOCTL_INQUIRE:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_ioctl_priv_inquire(dev, (int *) wrq->u.name);
		break;

	case PRISM2_IOCTL_MONITOR:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_ioctl_priv_monitor(dev, (int *) wrq->u.name);
		break;

	case PRISM2_IOCTL_RESET:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_ioctl_priv_reset(dev, (int *) wrq->u.name);
		break;

	case PRISM2_IOCTL_WDS_ADD:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_wds_add(local, wrq->u.ap_addr.sa_data, 1);
		break;

	case PRISM2_IOCTL_WDS_DEL:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_wds_del(local, wrq->u.ap_addr.sa_data, 1, 0);
		break;

	case PRISM2_IOCTL_SET_RID_WORD:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_ioctl_priv_set_rid_word(dev,
							  (int *) wrq->u.name);
		break;

#ifndef PRISM2_NO_KERNEL_IEEE80211_MGMT
	case PRISM2_IOCTL_MACCMD:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = ap_mac_cmd_ioctl(local, (int *) wrq->u.name);
		break;

	case PRISM2_IOCTL_ADDMAC:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = ap_control_add_mac(&local->ap->mac_restrictions,
					      wrq->u.ap_addr.sa_data);
		break;
	case PRISM2_IOCTL_DELMAC:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = ap_control_del_mac(&local->ap->mac_restrictions,
					      wrq->u.ap_addr.sa_data);
		break;
	case PRISM2_IOCTL_KICKMAC:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = ap_control_kick_mac(local->ap, local->dev,
					       wrq->u.ap_addr.sa_data);
		break;
#endif /* PRISM2_NO_KERNEL_IEEE80211_MGMT */


		/* Private ioctls that are not used with iwpriv;
		 * in SIOCDEVPRIVATE range */

#ifdef PRISM2_DOWNLOAD_SUPPORT
	case PRISM2_IOCTL_DOWNLOAD:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_ioctl_priv_download(local, &wrq->u.data);
		break;
#endif /* PRISM2_DOWNLOAD_SUPPORT */

	case PRISM2_IOCTL_HOSTAPD:
		if (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		else ret = prism2_ioctl_priv_hostapd(local, &wrq->u.data);
		break;

	default:
		ret = -EOPNOTSUPP;
		break;
	}

	return ret;
}