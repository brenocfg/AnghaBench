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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ int_block; } ;
struct bnx2x {TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ INT_BLOCK_HC ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  bnx2x_hc_ack_int (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_igu_ack_int (struct bnx2x*) ; 

__attribute__((used)) static inline u16 bnx2x_ack_int(struct bnx2x *bp)
{
	barrier();
	if (bp->common.int_block == INT_BLOCK_HC)
		return bnx2x_hc_ack_int(bp);
	else
		return bnx2x_igu_ack_int(bp);
}