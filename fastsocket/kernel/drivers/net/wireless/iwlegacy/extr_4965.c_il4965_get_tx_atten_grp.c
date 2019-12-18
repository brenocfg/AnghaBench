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
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CALIB_CH_GROUP_1 ; 
 int /*<<< orphan*/  CALIB_CH_GROUP_2 ; 
 int /*<<< orphan*/  CALIB_CH_GROUP_3 ; 
 int /*<<< orphan*/  CALIB_CH_GROUP_4 ; 
 int /*<<< orphan*/  CALIB_CH_GROUP_5 ; 
 scalar_t__ CALIB_IL_TX_ATTEN_GR1_FCH ; 
 scalar_t__ CALIB_IL_TX_ATTEN_GR1_LCH ; 
 scalar_t__ CALIB_IL_TX_ATTEN_GR2_FCH ; 
 scalar_t__ CALIB_IL_TX_ATTEN_GR2_LCH ; 
 scalar_t__ CALIB_IL_TX_ATTEN_GR3_FCH ; 
 scalar_t__ CALIB_IL_TX_ATTEN_GR3_LCH ; 
 scalar_t__ CALIB_IL_TX_ATTEN_GR4_FCH ; 
 scalar_t__ CALIB_IL_TX_ATTEN_GR4_LCH ; 
 scalar_t__ CALIB_IL_TX_ATTEN_GR5_FCH ; 
 scalar_t__ CALIB_IL_TX_ATTEN_GR5_LCH ; 
 int /*<<< orphan*/  EINVAL ; 

__attribute__((used)) static s32
il4965_get_tx_atten_grp(u16 channel)
{
	if (channel >= CALIB_IL_TX_ATTEN_GR5_FCH &&
	    channel <= CALIB_IL_TX_ATTEN_GR5_LCH)
		return CALIB_CH_GROUP_5;

	if (channel >= CALIB_IL_TX_ATTEN_GR1_FCH &&
	    channel <= CALIB_IL_TX_ATTEN_GR1_LCH)
		return CALIB_CH_GROUP_1;

	if (channel >= CALIB_IL_TX_ATTEN_GR2_FCH &&
	    channel <= CALIB_IL_TX_ATTEN_GR2_LCH)
		return CALIB_CH_GROUP_2;

	if (channel >= CALIB_IL_TX_ATTEN_GR3_FCH &&
	    channel <= CALIB_IL_TX_ATTEN_GR3_LCH)
		return CALIB_CH_GROUP_3;

	if (channel >= CALIB_IL_TX_ATTEN_GR4_FCH &&
	    channel <= CALIB_IL_TX_ATTEN_GR4_LCH)
		return CALIB_CH_GROUP_4;

	return -EINVAL;
}