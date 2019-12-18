#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  stops; } ;
struct sge_ctrl_txq {int full; TYPE_1__ q; } ;
struct fw_wr_hdr {int /*<<< orphan*/  lo; } ;

/* Variables and functions */
 int FW_WR_EQUEQ ; 
 int FW_WR_EQUIQ ; 
 scalar_t__ TXQ_STOP_THRES ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  reclaim_completed_tx_imm (TYPE_1__*) ; 
 scalar_t__ txq_avail (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ctrlq_check_stop(struct sge_ctrl_txq *q, struct fw_wr_hdr *wr)
{
	reclaim_completed_tx_imm(&q->q);
	if (unlikely(txq_avail(&q->q) < TXQ_STOP_THRES)) {
		wr->lo |= htonl(FW_WR_EQUEQ | FW_WR_EQUIQ);
		q->q.stops++;
		q->full = 1;
	}
}