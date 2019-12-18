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
typedef  size_t u8 ;
struct cos_help_data {struct cos_entry_help_data* data; } ;
struct cos_entry_help_data {size_t pri_join_mask; int /*<<< orphan*/  pausable; int /*<<< orphan*/  strict; int /*<<< orphan*/  cos_bw; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DCBX_STRICT_COS_HIGHEST ; 
 int /*<<< orphan*/  DCBX_INVALID_COS_BW ; 
 int /*<<< orphan*/  DCBX_IS_PFC_PRI_SOME_PAUSE (struct bnx2x*,size_t) ; 
 scalar_t__ bnx2x_dcbx_spread_strict_pri (struct bnx2x*,struct cos_help_data*,size_t,size_t,size_t) ; 

__attribute__((used)) static u8 bnx2x_dcbx_cee_fill_strict_pri(struct bnx2x *bp,
					 struct cos_help_data *cos_data,
					 u8 entry,
					 u8 num_spread_of_entries,
					 u8 strict_app_pris)
{
	if (bnx2x_dcbx_spread_strict_pri(bp, cos_data, entry,
					 num_spread_of_entries,
					 strict_app_pris)) {
		struct cos_entry_help_data *data = &cos_data->
						    data[entry];
		/* Fill BW entry */
		data->cos_bw = DCBX_INVALID_COS_BW;
		data->strict = BNX2X_DCBX_STRICT_COS_HIGHEST;
		data->pri_join_mask = strict_app_pris;
		data->pausable = DCBX_IS_PFC_PRI_SOME_PAUSE(bp,
				 data->pri_join_mask);
		return 1;
	}

	return num_spread_of_entries;
}