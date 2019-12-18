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
struct bnx2_tx_ring_info {scalar_t__ hw_tx_cons; } ;
struct bnx2_rx_ring_info {scalar_t__ rx_cons; } ;
struct bnx2_napi {struct bnx2_rx_ring_info rx_ring; struct bnx2_tx_ring_info tx_ring; } ;
struct bnx2 {int dummy; } ;

/* Variables and functions */
 scalar_t__ bnx2_get_hw_rx_cons (struct bnx2_napi*) ; 
 scalar_t__ bnx2_get_hw_tx_cons (struct bnx2_napi*) ; 
 scalar_t__ bnx2_rx_int (struct bnx2*,struct bnx2_napi*,int) ; 
 int /*<<< orphan*/  bnx2_tx_int (struct bnx2*,struct bnx2_napi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2_poll_work(struct bnx2 *bp, struct bnx2_napi *bnapi,
			  int work_done, int budget)
{
	struct bnx2_tx_ring_info *txr = &bnapi->tx_ring;
	struct bnx2_rx_ring_info *rxr = &bnapi->rx_ring;

	if (bnx2_get_hw_tx_cons(bnapi) != txr->hw_tx_cons)
		bnx2_tx_int(bp, bnapi, 0);

	if (bnx2_get_hw_rx_cons(bnapi) != rxr->rx_cons)
		work_done += bnx2_rx_int(bp, bnapi, budget - work_done);

	return work_done;
}