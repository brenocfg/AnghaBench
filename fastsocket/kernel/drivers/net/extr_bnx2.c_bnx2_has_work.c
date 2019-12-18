#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct status_block {scalar_t__ status_idx; int status_attn_bits; int status_attn_bits_ack; } ;
struct TYPE_2__ {struct status_block* msi; } ;
struct bnx2_napi {scalar_t__ cnic_tag; scalar_t__ cnic_present; TYPE_1__ status_blk; } ;

/* Variables and functions */
 int STATUS_ATTN_EVENTS ; 
 scalar_t__ bnx2_has_fast_work (struct bnx2_napi*) ; 

__attribute__((used)) static inline int
bnx2_has_work(struct bnx2_napi *bnapi)
{
	struct status_block *sblk = bnapi->status_blk.msi;

	if (bnx2_has_fast_work(bnapi))
		return 1;

#ifdef BCM_CNIC
	if (bnapi->cnic_present && (bnapi->cnic_tag != sblk->status_idx))
		return 1;
#endif

	if ((sblk->status_attn_bits & STATUS_ATTN_EVENTS) !=
	    (sblk->status_attn_bits_ack & STATUS_ATTN_EVENTS))
		return 1;

	return 0;
}