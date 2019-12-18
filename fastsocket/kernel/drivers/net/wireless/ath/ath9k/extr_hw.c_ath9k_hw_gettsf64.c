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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_TSF_L32 ; 
 int /*<<< orphan*/  AR_TSF_U32 ; 
 int ATH9K_MAX_TSF_READ ; 
 scalar_t__ REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

u64 ath9k_hw_gettsf64(struct ath_hw *ah)
{
	u32 tsf_lower, tsf_upper1, tsf_upper2;
	int i;

	tsf_upper1 = REG_READ(ah, AR_TSF_U32);
	for (i = 0; i < ATH9K_MAX_TSF_READ; i++) {
		tsf_lower = REG_READ(ah, AR_TSF_L32);
		tsf_upper2 = REG_READ(ah, AR_TSF_U32);
		if (tsf_upper2 == tsf_upper1)
			break;
		tsf_upper1 = tsf_upper2;
	}

	WARN_ON( i == ATH9K_MAX_TSF_READ );

	return (((u64)tsf_upper1 << 32) | tsf_lower);
}