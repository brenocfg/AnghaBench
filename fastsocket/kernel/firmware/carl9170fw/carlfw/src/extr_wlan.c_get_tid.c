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
typedef  int u16 ;
struct ieee80211_hdr {int dummy; } ;

/* Variables and functions */
 int IEEE80211_QOS_CTL_TID_MASK ; 
 int* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 

__attribute__((used)) static inline u16 get_tid(struct ieee80211_hdr *hdr)
{
	return (ieee80211_get_qos_ctl(hdr))[0] & IEEE80211_QOS_CTL_TID_MASK;
}