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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct ieee80211_rate {int /*<<< orphan*/  hw_value; } ;
struct b43legacy_wldev {TYPE_1__* wl; } ;
struct b43legacy_plcp_hdr4 {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  vif; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 scalar_t__ FCS_LEN ; 
 int /*<<< orphan*/  IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  b43legacy_generate_plcp_hdr (struct b43legacy_plcp_hdr4*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_shm_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ieee80211_generic_frame_duration (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct ieee80211_rate*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (scalar_t__) ; 

__attribute__((used)) static void b43legacy_write_probe_resp_plcp(struct b43legacy_wldev *dev,
					    u16 shm_offset, u16 size,
					    struct ieee80211_rate *rate)
{
	struct b43legacy_plcp_hdr4 plcp;
	u32 tmp;
	__le16 dur;

	plcp.data = 0;
	b43legacy_generate_plcp_hdr(&plcp, size + FCS_LEN, rate->hw_value);
	dur = ieee80211_generic_frame_duration(dev->wl->hw,
					       dev->wl->vif,
					       IEEE80211_BAND_2GHZ,
					       size,
					       rate);
	/* Write PLCP in two parts and timing for packet transfer */
	tmp = le32_to_cpu(plcp.data);
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, shm_offset,
			      tmp & 0xFFFF);
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, shm_offset + 2,
			      tmp >> 16);
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, shm_offset + 6,
			      le16_to_cpu(dur));
}