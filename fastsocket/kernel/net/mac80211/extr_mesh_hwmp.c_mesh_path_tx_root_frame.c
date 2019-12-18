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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int dot11MeshHWMPRootMode; int /*<<< orphan*/  element_ttl; int /*<<< orphan*/  dot11MeshHWMPactivePathToRootTimeout; scalar_t__ dot11MeshGateAnnouncementProtocol; int /*<<< orphan*/  dot11MeshHWMPRannInterval; } ;
struct ieee80211_if_mesh {int /*<<< orphan*/  preq_id; TYPE_3__ mshcfg; int /*<<< orphan*/  sn; } ;
struct TYPE_4__ {struct ieee80211_if_mesh mesh; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; TYPE_1__ u; } ;

/* Variables and functions */
 int IEEE80211_PREQ_PROACTIVE_PREP_FLAG ; 
 int IEEE80211_PREQ_TO_FLAG ; 
 int IEEE80211_PREQ_USN_FLAG ; 
#define  IEEE80211_PROACTIVE_PREQ_NO_PREP 130 
#define  IEEE80211_PROACTIVE_PREQ_WITH_PREP 129 
#define  IEEE80211_PROACTIVE_RANN 128 
 int /*<<< orphan*/  MPATH_PREQ ; 
 int /*<<< orphan*/  MPATH_RANN ; 
 int RANN_FLAG_IS_GATE ; 
 scalar_t__ broadcast_addr ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_path_sel_frame_tx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mhwmp_dbg (struct ieee80211_sub_if_data*,char*) ; 

void mesh_path_tx_root_frame(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u32 interval = ifmsh->mshcfg.dot11MeshHWMPRannInterval;
	u8 flags, target_flags = 0;

	flags = (ifmsh->mshcfg.dot11MeshGateAnnouncementProtocol)
			? RANN_FLAG_IS_GATE : 0;

	switch (ifmsh->mshcfg.dot11MeshHWMPRootMode) {
	case IEEE80211_PROACTIVE_RANN:
		mesh_path_sel_frame_tx(MPATH_RANN, flags, sdata->vif.addr,
			       cpu_to_le32(++ifmsh->sn),
			       0, NULL, 0, broadcast_addr,
			       0, ifmsh->mshcfg.element_ttl,
			       cpu_to_le32(interval), 0, 0, sdata);
		break;
	case IEEE80211_PROACTIVE_PREQ_WITH_PREP:
		flags |= IEEE80211_PREQ_PROACTIVE_PREP_FLAG;
	case IEEE80211_PROACTIVE_PREQ_NO_PREP:
		interval = ifmsh->mshcfg.dot11MeshHWMPactivePathToRootTimeout;
		target_flags |= IEEE80211_PREQ_TO_FLAG |
				IEEE80211_PREQ_USN_FLAG;
		mesh_path_sel_frame_tx(MPATH_PREQ, flags, sdata->vif.addr,
				cpu_to_le32(++ifmsh->sn), target_flags,
				(u8 *) broadcast_addr, 0, broadcast_addr,
				0, ifmsh->mshcfg.element_ttl,
				cpu_to_le32(interval),
				0, cpu_to_le32(ifmsh->preq_id++), sdata);
		break;
	default:
		mhwmp_dbg(sdata, "Proactive mechanism not supported\n");
		return;
	}
}