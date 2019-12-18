#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int plcp; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int IWL_FIRST_OFDM_RATE ; 
 int IWL_LAST_OFDM_RATE ; 
 int IWL_RATE_9M_INDEX ; 
 int IWL_RATE_MIMO2_6M_PLCP ; 
 int IWL_RATE_MIMO3_6M_PLCP ; 
 int RATE_MCS_HT_MSK ; 
 TYPE_1__* iwl_rates ; 
 int rs_extract_rate (int) ; 

__attribute__((used)) static int iwl_hwrate_to_plcp_idx(u32 rate_n_flags)
{
	int idx = 0;

	/* HT rate format */
	if (rate_n_flags & RATE_MCS_HT_MSK) {
		idx = rs_extract_rate(rate_n_flags);

		if (idx >= IWL_RATE_MIMO3_6M_PLCP)
			idx = idx - IWL_RATE_MIMO3_6M_PLCP;
		else if (idx >= IWL_RATE_MIMO2_6M_PLCP)
			idx = idx - IWL_RATE_MIMO2_6M_PLCP;

		idx += IWL_FIRST_OFDM_RATE;
		/* skip 9M not supported in ht*/
		if (idx >= IWL_RATE_9M_INDEX)
			idx += 1;
		if ((idx >= IWL_FIRST_OFDM_RATE) && (idx <= IWL_LAST_OFDM_RATE))
			return idx;

	/* legacy rate format, search for match in table */
	} else {
		for (idx = 0; idx < ARRAY_SIZE(iwl_rates); idx++)
			if (iwl_rates[idx].plcp ==
					rs_extract_rate(rate_n_flags))
				return idx;
	}

	return -1;
}