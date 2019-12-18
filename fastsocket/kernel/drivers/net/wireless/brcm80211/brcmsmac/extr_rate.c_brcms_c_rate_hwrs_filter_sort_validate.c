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
typedef  size_t uint ;
typedef  int u8 ;
struct brcms_c_rateset {size_t count; int* rates; int* mcs; } ;
typedef  int /*<<< orphan*/  rateset ;

/* Variables and functions */
 int BRCMS_RATE_MASK ; 
 int BRCM_MAXRATE ; 
 size_t MCSSET_LEN ; 
 scalar_t__ brcms_c_rateset_valid (struct brcms_c_rateset*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* rate_info ; 

bool
brcms_c_rate_hwrs_filter_sort_validate(struct brcms_c_rateset *rs,
				   const struct brcms_c_rateset *hw_rs,
				   bool check_brate, u8 txstreams)
{
	u8 rateset[BRCM_MAXRATE + 1];
	u8 r;
	uint count;
	uint i;

	memset(rateset, 0, sizeof(rateset));
	count = rs->count;

	for (i = 0; i < count; i++) {
		/* mask off "basic rate" bit, BRCMS_RATE_FLAG */
		r = (int)rs->rates[i] & BRCMS_RATE_MASK;
		if ((r > BRCM_MAXRATE) || (rate_info[r] == 0))
			continue;
		rateset[r] = rs->rates[i];	/* preserve basic bit! */
	}

	/* fill out the rates in order, looking at only supported rates */
	count = 0;
	for (i = 0; i < hw_rs->count; i++) {
		r = hw_rs->rates[i] & BRCMS_RATE_MASK;
		if (rateset[r])
			rs->rates[count++] = rateset[r];
	}

	rs->count = count;

	/* only set the mcs rate bit if the equivalent hw mcs bit is set */
	for (i = 0; i < MCSSET_LEN; i++)
		rs->mcs[i] = (rs->mcs[i] & hw_rs->mcs[i]);

	if (brcms_c_rateset_valid(rs, check_brate))
		return true;
	else
		return false;
}