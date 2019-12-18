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
struct brcms_c_info {int SRL; int LRL; void** wme_retries; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDCF_LONG ; 
 int /*<<< orphan*/  EDCF_SHORT ; 
 int EINVAL ; 
 int IEEE80211_NUM_ACS ; 
 int RETRY_SHORT_MAX ; 
 void* SFIELD (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcms_b_retrylimit_upd (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  brcms_c_wme_retries_write (struct brcms_c_info*) ; 

int brcms_c_set_rate_limit(struct brcms_c_info *wlc, u16 srl, u16 lrl)
{
	int ac;

	if (srl < 1 || srl > RETRY_SHORT_MAX ||
	    lrl < 1 || lrl > RETRY_SHORT_MAX)
		return -EINVAL;

	wlc->SRL = srl;
	wlc->LRL = lrl;

	brcms_b_retrylimit_upd(wlc->hw, wlc->SRL, wlc->LRL);

	for (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		wlc->wme_retries[ac] =	SFIELD(wlc->wme_retries[ac],
					       EDCF_SHORT,  wlc->SRL);
		wlc->wme_retries[ac] =	SFIELD(wlc->wme_retries[ac],
					       EDCF_LONG, wlc->LRL);
	}
	brcms_c_wme_retries_write(wlc);

	return 0;
}