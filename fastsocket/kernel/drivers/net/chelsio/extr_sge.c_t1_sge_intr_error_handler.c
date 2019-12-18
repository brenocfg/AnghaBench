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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pkt_mismatch; int /*<<< orphan*/  pkt_too_big; int /*<<< orphan*/  freelistQ_empty; int /*<<< orphan*/  respQ_overflow; int /*<<< orphan*/  respQ_empty; } ;
struct sge {TYPE_1__ stats; struct adapter* adapter; } ;
struct adapter {int flags; scalar_t__ regs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ A_SG_INT_CAUSE ; 
 int /*<<< orphan*/  CH_ALERT (char*,int /*<<< orphan*/ ) ; 
 int F_FL_EXHAUSTED ; 
 int F_PACKET_MISMATCH ; 
 int F_PACKET_TOO_BIG ; 
 int F_RESPQ_EXHAUSTED ; 
 int F_RESPQ_OVERFLOW ; 
 int SGE_INT_FATAL ; 
 int TSO_CAPABLE ; 
 int /*<<< orphan*/  freelQs_empty (struct sge*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  t1_fatal_err (struct adapter*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int t1_sge_intr_error_handler(struct sge *sge)
{
	struct adapter *adapter = sge->adapter;
	u32 cause = readl(adapter->regs + A_SG_INT_CAUSE);

	if (adapter->flags & TSO_CAPABLE)
		cause &= ~F_PACKET_TOO_BIG;
	if (cause & F_RESPQ_EXHAUSTED)
		sge->stats.respQ_empty++;
	if (cause & F_RESPQ_OVERFLOW) {
		sge->stats.respQ_overflow++;
		CH_ALERT("%s: SGE response queue overflow\n",
			 adapter->name);
	}
	if (cause & F_FL_EXHAUSTED) {
		sge->stats.freelistQ_empty++;
		freelQs_empty(sge);
	}
	if (cause & F_PACKET_TOO_BIG) {
		sge->stats.pkt_too_big++;
		CH_ALERT("%s: SGE max packet size exceeded\n",
			 adapter->name);
	}
	if (cause & F_PACKET_MISMATCH) {
		sge->stats.pkt_mismatch++;
		CH_ALERT("%s: SGE packet mismatch\n", adapter->name);
	}
	if (cause & SGE_INT_FATAL)
		t1_fatal_err(adapter);

	writel(cause, adapter->regs + A_SG_INT_CAUSE);
	return 0;
}