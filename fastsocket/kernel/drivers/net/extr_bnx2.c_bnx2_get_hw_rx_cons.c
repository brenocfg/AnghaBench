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
typedef  int u16 ;
struct bnx2_napi {int* hw_rx_cons_ptr; } ;

/* Variables and functions */
 int BNX2_MAX_RX_DESC_CNT ; 
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline u16
bnx2_get_hw_rx_cons(struct bnx2_napi *bnapi)
{
	u16 cons;

	/* Tell compiler that status block fields can change. */
	barrier();
	cons = *bnapi->hw_rx_cons_ptr;
	barrier();
	if (unlikely((cons & BNX2_MAX_RX_DESC_CNT) == BNX2_MAX_RX_DESC_CNT))
		cons++;
	return cons;
}