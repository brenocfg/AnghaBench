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
typedef  int u8 ;
struct sta_info {scalar_t__ plink_state; int local_pm; } ;
struct TYPE_3__ {int nonpeer_pm; scalar_t__ ps_peers_deep_sleep; } ;
struct TYPE_4__ {TYPE_1__ mesh; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;
typedef  enum nl80211_mesh_power_mode { ____Placeholder_nl80211_mesh_power_mode } nl80211_mesh_power_mode ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FCTL_PM ; 
 int IEEE80211_QOS_CTL_MESH_PS_LEVEL ; 
 int NL80211_MESH_POWER_ACTIVE ; 
 int NL80211_MESH_POWER_DEEP_SLEEP ; 
 scalar_t__ NL80211_PLINK_ESTAB ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_unicast_ether_addr (int /*<<< orphan*/ ) ; 

void ieee80211_mps_set_frame_flags(struct ieee80211_sub_if_data *sdata,
				   struct sta_info *sta,
				   struct ieee80211_hdr *hdr)
{
	enum nl80211_mesh_power_mode pm;
	u8 *qc;

	if (WARN_ON(is_unicast_ether_addr(hdr->addr1) &&
		    ieee80211_is_data_qos(hdr->frame_control) &&
		    !sta))
		return;

	if (is_unicast_ether_addr(hdr->addr1) &&
	    ieee80211_is_data_qos(hdr->frame_control) &&
	    sta->plink_state == NL80211_PLINK_ESTAB)
		pm = sta->local_pm;
	else
		pm = sdata->u.mesh.nonpeer_pm;

	if (pm == NL80211_MESH_POWER_ACTIVE)
		hdr->frame_control &= cpu_to_le16(~IEEE80211_FCTL_PM);
	else
		hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);

	if (!ieee80211_is_data_qos(hdr->frame_control))
		return;

	qc = ieee80211_get_qos_ctl(hdr);

	if ((is_unicast_ether_addr(hdr->addr1) &&
	     pm == NL80211_MESH_POWER_DEEP_SLEEP) ||
	    (is_multicast_ether_addr(hdr->addr1) &&
	     sdata->u.mesh.ps_peers_deep_sleep > 0))
		qc[1] |= (IEEE80211_QOS_CTL_MESH_PS_LEVEL >> 8);
	else
		qc[1] &= ~(IEEE80211_QOS_CTL_MESH_PS_LEVEL >> 8);
}