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
struct bnx2x_fp_txdata {scalar_t__ tx_pkt_cons; int /*<<< orphan*/ * tx_cons_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int bnx2x_tx_queue_has_work(struct bnx2x_fp_txdata *txdata)
{
	u16 hw_cons;

	/* Tell compiler that status block fields can change */
	barrier();
	hw_cons = le16_to_cpu(*txdata->tx_cons_sb);
	return hw_cons != txdata->tx_pkt_cons;
}