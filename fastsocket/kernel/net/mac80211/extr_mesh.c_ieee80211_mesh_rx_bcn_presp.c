#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee802_11_elems {int /*<<< orphan*/ * ds_params; scalar_t__ rsn; int /*<<< orphan*/  mesh_config; int /*<<< orphan*/  mesh_id; } ;
struct ieee80211_if_mesh {scalar_t__ security; TYPE_6__* sync_ops; } ;
struct TYPE_10__ {struct ieee80211_if_mesh mesh; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; TYPE_1__ vif; struct ieee80211_local* local; } ;
struct ieee80211_rx_status {int band; int freq; } ;
struct TYPE_8__ {scalar_t__ variable; } ;
struct TYPE_9__ {TYPE_2__ probe_resp; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  sa; TYPE_3__ u; int /*<<< orphan*/  da; } ;
struct TYPE_11__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_5__ hw; } ;
struct ieee80211_channel {int flags; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_12__ {int /*<<< orphan*/  (* rx_bcn_presp ) (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,struct ieee80211_mgmt*,struct ieee802_11_elems*,struct ieee80211_rx_status*) ;} ;

/* Variables and functions */
 int IEEE80211_CHAN_DISABLED ; 
 scalar_t__ IEEE80211_MESH_SEC_NONE ; 
 int /*<<< orphan*/  IEEE80211_STYPE_PROBE_RESP ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_channel_to_frequency (int /*<<< orphan*/ ,int) ; 
 struct ieee80211_channel* ieee80211_get_channel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee802_11_parse_elems (scalar_t__,size_t,int,struct ieee802_11_elems*) ; 
 scalar_t__ mesh_matches_local (struct ieee80211_sub_if_data*,struct ieee802_11_elems*) ; 
 int /*<<< orphan*/  mesh_neighbour_update (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,struct ieee802_11_elems*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,struct ieee80211_mgmt*,struct ieee802_11_elems*,struct ieee80211_rx_status*) ; 

__attribute__((used)) static void ieee80211_mesh_rx_bcn_presp(struct ieee80211_sub_if_data *sdata,
					u16 stype,
					struct ieee80211_mgmt *mgmt,
					size_t len,
					struct ieee80211_rx_status *rx_status)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	struct ieee802_11_elems elems;
	struct ieee80211_channel *channel;
	size_t baselen;
	int freq;
	enum ieee80211_band band = rx_status->band;

	/* ignore ProbeResp to foreign address */
	if (stype == IEEE80211_STYPE_PROBE_RESP &&
	    !ether_addr_equal(mgmt->da, sdata->vif.addr))
		return;

	baselen = (u8 *) mgmt->u.probe_resp.variable - (u8 *) mgmt;
	if (baselen > len)
		return;

	ieee802_11_parse_elems(mgmt->u.probe_resp.variable, len - baselen,
			       false, &elems);

	/* ignore non-mesh or secure / unsecure mismatch */
	if ((!elems.mesh_id || !elems.mesh_config) ||
	    (elems.rsn && sdata->u.mesh.security == IEEE80211_MESH_SEC_NONE) ||
	    (!elems.rsn && sdata->u.mesh.security != IEEE80211_MESH_SEC_NONE))
		return;

	if (elems.ds_params)
		freq = ieee80211_channel_to_frequency(elems.ds_params[0], band);
	else
		freq = rx_status->freq;

	channel = ieee80211_get_channel(local->hw.wiphy, freq);

	if (!channel || channel->flags & IEEE80211_CHAN_DISABLED)
		return;

	if (mesh_matches_local(sdata, &elems))
		mesh_neighbour_update(sdata, mgmt->sa, &elems);

	if (ifmsh->sync_ops)
		ifmsh->sync_ops->rx_bcn_presp(sdata,
			stype, mgmt, &elems, rx_status);
}