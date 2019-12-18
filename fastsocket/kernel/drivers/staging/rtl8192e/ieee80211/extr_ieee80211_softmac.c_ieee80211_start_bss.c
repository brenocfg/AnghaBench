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
struct ieee80211_device {scalar_t__ state; int actscanning; int /*<<< orphan*/  lock; int /*<<< orphan*/  bGlobalDomain; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_NOLINK ; 
 int /*<<< orphan*/  IS_COUNTRY_IE_VALID (struct ieee80211_device*) ; 
 scalar_t__ IS_DOT11D_ENABLE (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_softmac_check_all_nets (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_start_scan (struct ieee80211_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ieee80211_start_bss(struct ieee80211_device *ieee)
{
	unsigned long flags;
#ifdef ENABLE_DOT11D
	//
	// Ref: 802.11d 11.1.3.3
	// STA shall not start a BSS unless properly formed Beacon frame including a Country IE.
	//
	if(IS_DOT11D_ENABLE(ieee) && !IS_COUNTRY_IE_VALID(ieee))
	{
		if(! ieee->bGlobalDomain)
		{
			return;
		}
	}
#endif
	/* check if we have already found the net we
	 * are interested in (if any).
	 * if not (we are disassociated and we are not
	 * in associating / authenticating phase) start the background scanning.
	 */
	ieee80211_softmac_check_all_nets(ieee);

	/* ensure no-one start an associating process (thus setting
	 * the ieee->state to ieee80211_ASSOCIATING) while we
	 * have just cheked it and we are going to enable scan.
	 * The ieee80211_new_net function is always called with
	 * lock held (from both ieee80211_softmac_check_all_nets and
	 * the rx path), so we cannot be in the middle of such function
	 */
	spin_lock_irqsave(&ieee->lock, flags);

	if (ieee->state == IEEE80211_NOLINK){
		ieee->actscanning = true;
		ieee80211_start_scan(ieee);
	}
	spin_unlock_irqrestore(&ieee->lock, flags);
}