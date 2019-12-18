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
typedef  int u32 ;

/* Variables and functions */
 int IEEE80211_TX_STAT_ACK ; 
 int IEEE80211_TX_STAT_TX_FILTERED ; 
#define  TX_STATUS_DIRECT_DONE 130 
#define  TX_STATUS_FAIL_DEST_PS 129 
 int TX_STATUS_MSK ; 
#define  TX_STATUS_SUCCESS 128 

__attribute__((used)) static inline u32
il4965_tx_status_to_mac80211(u32 status)
{
	status &= TX_STATUS_MSK;

	switch (status) {
	case TX_STATUS_SUCCESS:
	case TX_STATUS_DIRECT_DONE:
		return IEEE80211_TX_STAT_ACK;
	case TX_STATUS_FAIL_DEST_PS:
		return IEEE80211_TX_STAT_TX_FILTERED;
	default:
		return 0;
	}
}