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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  VPIF_CH0_CTRL ; 
 int /*<<< orphan*/  VPIF_CH1_CTRL ; 
 int /*<<< orphan*/  VPIF_CH_HANC_EN_BIT ; 
 int /*<<< orphan*/  VPIF_CH_VANC_EN_BIT ; 
 int /*<<< orphan*/  vpif_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void enable_raw_feature(u8 channel_id, u8 index)
{
	u32 ctrl_reg;
	if (0 == channel_id)
		ctrl_reg = VPIF_CH0_CTRL;
	else
		ctrl_reg = VPIF_CH1_CTRL;

	if (1 == index)
		vpif_set_bit(ctrl_reg, VPIF_CH_VANC_EN_BIT);
	else
		vpif_set_bit(ctrl_reg, VPIF_CH_HANC_EN_BIT);
}