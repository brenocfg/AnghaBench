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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct ieee80211_hdr_3addr {int /*<<< orphan*/  frame_ctl; } ;
struct TYPE_3__ {int /*<<< orphan*/  tid; } ;
struct TYPE_4__ {TYPE_1__ field; } ;
typedef  TYPE_2__ frameqos ;

/* Variables and functions */
 int IEEE80211_FCTL_FROMDS ; 
 int IEEE80211_FCTL_TODS ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 Frame_QoSTID(u8 *buf)
{
	struct ieee80211_hdr_3addr *hdr = (struct ieee80211_hdr_3addr *)buf;
	u16 fc = le16_to_cpu(hdr->frame_ctl);

	return (u8)((frameqos *)(buf +
		(((fc & IEEE80211_FCTL_TODS) &&
		  (fc & IEEE80211_FCTL_FROMDS)) ? 30 : 24)))->field.tid;
}