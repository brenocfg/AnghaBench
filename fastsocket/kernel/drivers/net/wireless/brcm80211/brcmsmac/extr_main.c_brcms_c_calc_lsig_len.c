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
typedef  int uint ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct brcms_c_info {int dummy; } ;

/* Variables and functions */
 int APHY_SERVICE_NBITS ; 
 int APHY_TAIL_NBITS ; 
 int CEIL (int,int) ; 
 int RSPEC_RATE_MASK ; 
 scalar_t__ is_mcs_rate (int) ; 
 int mcs_2_rate (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mcs_2_txstreams (int) ; 
 int /*<<< orphan*/  rspec_is40mhz (int) ; 
 int /*<<< orphan*/  rspec_issgi (int) ; 
 int rspec_stc (int) ; 

u16
brcms_c_calc_lsig_len(struct brcms_c_info *wlc, u32 ratespec,
		      uint mac_len)
{
	uint nsyms, len = 0, kNdps;

	if (is_mcs_rate(ratespec)) {
		uint mcs = ratespec & RSPEC_RATE_MASK;
		int tot_streams = (mcs_2_txstreams(mcs) + 1) +
				  rspec_stc(ratespec);

		/*
		 * the payload duration calculation matches that
		 * of regular ofdm
		 */
		/* 1000Ndbps = kbps * 4 */
		kNdps = mcs_2_rate(mcs, rspec_is40mhz(ratespec),
				   rspec_issgi(ratespec)) * 4;

		if (rspec_stc(ratespec) == 0)
			nsyms =
			    CEIL((APHY_SERVICE_NBITS + 8 * mac_len +
				  APHY_TAIL_NBITS) * 1000, kNdps);
		else
			/* STBC needs to have even number of symbols */
			nsyms =
			    2 *
			    CEIL((APHY_SERVICE_NBITS + 8 * mac_len +
				  APHY_TAIL_NBITS) * 1000, 2 * kNdps);

		/* (+3) account for HT-SIG(2) and HT-STF(1) */
		nsyms += (tot_streams + 3);
		/*
		 * 3 bytes/symbol @ legacy 6Mbps rate
		 * (-3) excluding service bits and tail bits
		 */
		len = (3 * nsyms) - 3;
	}

	return (u16) len;
}