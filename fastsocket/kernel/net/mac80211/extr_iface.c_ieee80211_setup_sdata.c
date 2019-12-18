#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * bssid; } ;
struct TYPE_18__ {int type; int p2p; int /*<<< orphan*/ * addr; TYPE_7__ bss_conf; } ;
struct TYPE_14__ {int /*<<< orphan*/ * bssid; } ;
struct TYPE_13__ {int /*<<< orphan*/ * bssid; } ;
struct TYPE_11__ {int /*<<< orphan*/  bc_buf; } ;
struct TYPE_12__ {int /*<<< orphan*/  vlans; TYPE_2__ ps; } ;
struct TYPE_17__ {int mntr_flags; TYPE_5__ ibss; TYPE_4__ mgd; TYPE_3__ ap; } ;
struct TYPE_10__ {int iftype; } ;
struct ieee80211_sub_if_data {int control_port_no_encrypt; TYPE_9__ vif; TYPE_8__ u; TYPE_6__* dev; int /*<<< orphan*/  recalc_smps; int /*<<< orphan*/  work; int /*<<< orphan*/  skb_queue; scalar_t__ noack_map; int /*<<< orphan*/  control_port_protocol; TYPE_1__ wdev; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_15__ {int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ARPHRD_IEEE80211_RADIOTAP ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  ETH_P_PAE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MONITOR_FLAG_CONTROL ; 
 int MONITOR_FLAG_OTHER_BSS ; 
#define  NL80211_IFTYPE_ADHOC 139 
#define  NL80211_IFTYPE_AP 138 
#define  NL80211_IFTYPE_AP_VLAN 137 
#define  NL80211_IFTYPE_MESH_POINT 136 
#define  NL80211_IFTYPE_MONITOR 135 
#define  NL80211_IFTYPE_P2P_CLIENT 134 
#define  NL80211_IFTYPE_P2P_DEVICE 133 
#define  NL80211_IFTYPE_P2P_GO 132 
#define  NL80211_IFTYPE_STATION 131 
#define  NL80211_IFTYPE_UNSPECIFIED 130 
#define  NL80211_IFTYPE_WDS 129 
#define  NUM_NL80211_IFTYPES 128 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_dataif_ops ; 
 int /*<<< orphan*/  ieee80211_debugfs_add_netdev (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_ibss_setup_sdata (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_iface_work ; 
 int /*<<< orphan*/  ieee80211_mesh_init_sdata (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_monitorif_ops ; 
 int /*<<< orphan*/  ieee80211_recalc_smps_work ; 
 int /*<<< orphan*/  ieee80211_sta_setup_sdata (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_vif_is_mesh (TYPE_9__*) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_setup_sdata(struct ieee80211_sub_if_data *sdata,
				  enum nl80211_iftype type)
{
	/* clear type-dependent union */
	memset(&sdata->u, 0, sizeof(sdata->u));

	/* and set some type-dependent values */
	sdata->vif.type = type;
	sdata->vif.p2p = false;
	sdata->wdev.iftype = type;

	sdata->control_port_protocol = cpu_to_be16(ETH_P_PAE);
	sdata->control_port_no_encrypt = false;

	sdata->noack_map = 0;

	/* only monitor/p2p-device differ */
	if (sdata->dev) {
		sdata->dev->netdev_ops = &ieee80211_dataif_ops;
		sdata->dev->type = ARPHRD_ETHER;
	}

	skb_queue_head_init(&sdata->skb_queue);
	INIT_WORK(&sdata->work, ieee80211_iface_work);
	INIT_WORK(&sdata->recalc_smps, ieee80211_recalc_smps_work);

	switch (type) {
	case NL80211_IFTYPE_P2P_GO:
		type = NL80211_IFTYPE_AP;
		sdata->vif.type = type;
		sdata->vif.p2p = true;
		/* fall through */
	case NL80211_IFTYPE_AP:
		skb_queue_head_init(&sdata->u.ap.ps.bc_buf);
		INIT_LIST_HEAD(&sdata->u.ap.vlans);
		sdata->vif.bss_conf.bssid = sdata->vif.addr;
		break;
	case NL80211_IFTYPE_P2P_CLIENT:
		type = NL80211_IFTYPE_STATION;
		sdata->vif.type = type;
		sdata->vif.p2p = true;
		/* fall through */
	case NL80211_IFTYPE_STATION:
		sdata->vif.bss_conf.bssid = sdata->u.mgd.bssid;
		ieee80211_sta_setup_sdata(sdata);
		break;
	case NL80211_IFTYPE_ADHOC:
		sdata->vif.bss_conf.bssid = sdata->u.ibss.bssid;
		ieee80211_ibss_setup_sdata(sdata);
		break;
	case NL80211_IFTYPE_MESH_POINT:
		if (ieee80211_vif_is_mesh(&sdata->vif))
			ieee80211_mesh_init_sdata(sdata);
		break;
	case NL80211_IFTYPE_MONITOR:
		sdata->dev->type = ARPHRD_IEEE80211_RADIOTAP;
		sdata->dev->netdev_ops = &ieee80211_monitorif_ops;
		sdata->u.mntr_flags = MONITOR_FLAG_CONTROL |
				      MONITOR_FLAG_OTHER_BSS;
		break;
	case NL80211_IFTYPE_WDS:
		sdata->vif.bss_conf.bssid = NULL;
		break;
	case NL80211_IFTYPE_AP_VLAN:
		break;
	case NL80211_IFTYPE_P2P_DEVICE:
		sdata->vif.bss_conf.bssid = sdata->vif.addr;
		break;
	case NL80211_IFTYPE_UNSPECIFIED:
	case NUM_NL80211_IFTYPES:
		BUG();
		break;
	}

	ieee80211_debugfs_add_netdev(sdata);
}