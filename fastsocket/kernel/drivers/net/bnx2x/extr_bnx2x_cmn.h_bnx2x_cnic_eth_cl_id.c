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
struct bnx2x {int pf_num; scalar_t__ cnic_base_cl_id; } ;

/* Variables and functions */
 int BNX2X_MAX_CNIC_ETH_CL_ID_IDX ; 

__attribute__((used)) static inline u8 bnx2x_cnic_eth_cl_id(struct bnx2x *bp, u8 cl_idx)
{
	return bp->cnic_base_cl_id + cl_idx +
		(bp->pf_num >> 1) * BNX2X_MAX_CNIC_ETH_CL_ID_IDX;
}