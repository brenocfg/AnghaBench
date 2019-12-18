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
struct brcms_c_info {TYPE_1__* stf; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {int rxstreams; } ;

/* Variables and functions */
 scalar_t__ BRCMS_STF_SS_STBC_RX (struct brcms_c_info*) ; 
 scalar_t__ HT_CAP_RX_STBC_NO ; 
 scalar_t__ HT_CAP_RX_STBC_ONE_STREAM ; 
 int /*<<< orphan*/  brcms_c_stf_stbc_rx_ht_update (struct brcms_c_info*,scalar_t__) ; 

bool brcms_c_stf_stbc_rx_set(struct brcms_c_info *wlc, s32 int_val)
{
	if ((int_val != HT_CAP_RX_STBC_NO)
	    && (int_val != HT_CAP_RX_STBC_ONE_STREAM))
		return false;

	if (BRCMS_STF_SS_STBC_RX(wlc)) {
		if ((int_val != HT_CAP_RX_STBC_NO)
		    && (wlc->stf->rxstreams == 1))
			return false;
	}

	brcms_c_stf_stbc_rx_ht_update(wlc, int_val);
	return true;
}