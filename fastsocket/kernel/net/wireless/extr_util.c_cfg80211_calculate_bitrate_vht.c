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
struct rate_info {int mcs; int flags; int nss; } ;

/* Variables and functions */
 int RATE_INFO_FLAGS_160_MHZ_WIDTH ; 
 int RATE_INFO_FLAGS_40_MHZ_WIDTH ; 
 int RATE_INFO_FLAGS_80P80_MHZ_WIDTH ; 
 int RATE_INFO_FLAGS_80_MHZ_WIDTH ; 
 int RATE_INFO_FLAGS_SHORT_GI ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

__attribute__((used)) static u32 cfg80211_calculate_bitrate_vht(struct rate_info *rate)
{
	static const u32 base[4][10] = {
		{   6500000,
		   13000000,
		   19500000,
		   26000000,
		   39000000,
		   52000000,
		   58500000,
		   65000000,
		   78000000,
		   0,
		},
		{  13500000,
		   27000000,
		   40500000,
		   54000000,
		   81000000,
		  108000000,
		  121500000,
		  135000000,
		  162000000,
		  180000000,
		},
		{  29300000,
		   58500000,
		   87800000,
		  117000000,
		  175500000,
		  234000000,
		  263300000,
		  292500000,
		  351000000,
		  390000000,
		},
		{  58500000,
		  117000000,
		  175500000,
		  234000000,
		  351000000,
		  468000000,
		  526500000,
		  585000000,
		  702000000,
		  780000000,
		},
	};
	u32 bitrate;
	int idx;

	if (WARN_ON_ONCE(rate->mcs > 9))
		return 0;

	idx = rate->flags & (RATE_INFO_FLAGS_160_MHZ_WIDTH |
			     RATE_INFO_FLAGS_80P80_MHZ_WIDTH) ? 3 :
		  rate->flags & RATE_INFO_FLAGS_80_MHZ_WIDTH ? 2 :
		  rate->flags & RATE_INFO_FLAGS_40_MHZ_WIDTH ? 1 : 0;

	bitrate = base[idx][rate->mcs];
	bitrate *= rate->nss;

	if (rate->flags & RATE_INFO_FLAGS_SHORT_GI)
		bitrate = (bitrate / 9) * 10;

	/* do NOT round down here */
	return (bitrate + 50000) / 100000;
}