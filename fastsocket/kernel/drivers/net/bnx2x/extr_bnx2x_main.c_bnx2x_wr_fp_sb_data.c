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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 scalar_t__ CSTORM_STATUS_BLOCK_DATA_OFFSET (int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 

__attribute__((used)) static void bnx2x_wr_fp_sb_data(struct bnx2x *bp,
				int fw_sb_id,
				u32 *sb_data_p,
				u32 data_size)
{
	int index;
	for (index = 0; index < data_size; index++)
		REG_WR(bp, BAR_CSTRORM_INTMEM +
			CSTORM_STATUS_BLOCK_DATA_OFFSET(fw_sb_id) +
			sizeof(u32)*index,
			*(sb_data_p + index));
}