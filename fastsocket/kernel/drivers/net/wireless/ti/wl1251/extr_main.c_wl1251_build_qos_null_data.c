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
typedef  int /*<<< orphan*/  template ;
struct wl1251 {int /*<<< orphan*/  bssid; int /*<<< orphan*/  mac_addr; } ;
struct ieee80211_qos_hdr {void* qos_ctrl; void* frame_control; int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_QOS_NULL_DATA ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_FCTL_TODS ; 
 int IEEE80211_FTYPE_DATA ; 
 int IEEE80211_STYPE_QOS_NULLFUNC ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_qos_hdr*,int /*<<< orphan*/ ,int) ; 
 int wl1251_cmd_template_set (struct wl1251*,int /*<<< orphan*/ ,struct ieee80211_qos_hdr*,int) ; 

__attribute__((used)) static int wl1251_build_qos_null_data(struct wl1251 *wl)
{
	struct ieee80211_qos_hdr template;

	memset(&template, 0, sizeof(template));

	memcpy(template.addr1, wl->bssid, ETH_ALEN);
	memcpy(template.addr2, wl->mac_addr, ETH_ALEN);
	memcpy(template.addr3, wl->bssid, ETH_ALEN);

	template.frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					     IEEE80211_STYPE_QOS_NULLFUNC |
					     IEEE80211_FCTL_TODS);

	/* FIXME: not sure what priority to use here */
	template.qos_ctrl = cpu_to_le16(0);

	return wl1251_cmd_template_set(wl, CMD_QOS_NULL_DATA, &template,
				       sizeof(template));
}