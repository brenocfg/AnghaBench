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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  stops; } ;
struct sge_ofld_txq {int full; TYPE_1__ q; } ;
struct fw_wr_hdr {int /*<<< orphan*/  lo; } ;

/* Variables and functions */
 int FW_WR_EQUEQ ; 
 int FW_WR_EQUIQ ; 
 int /*<<< orphan*/  htonl (int) ; 

__attribute__((used)) static void ofldtxq_stop(struct sge_ofld_txq *q, struct sk_buff *skb)
{
	struct fw_wr_hdr *wr = (struct fw_wr_hdr *)skb->data;

	wr->lo |= htonl(FW_WR_EQUEQ | FW_WR_EQUIQ);
	q->q.stops++;
	q->full = 1;
}