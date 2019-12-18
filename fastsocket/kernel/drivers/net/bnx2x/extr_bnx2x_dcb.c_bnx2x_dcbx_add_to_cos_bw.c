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
struct cos_entry_help_data {scalar_t__ cos_bw; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ DCBX_INVALID_COS_BW ; 

__attribute__((used)) static inline void bnx2x_dcbx_add_to_cos_bw(struct bnx2x *bp,
					    struct cos_entry_help_data *data,
					    u8 pg_bw)
{
	if (data->cos_bw == DCBX_INVALID_COS_BW)
		data->cos_bw = pg_bw;
	else
		data->cos_bw += pg_bw;
}