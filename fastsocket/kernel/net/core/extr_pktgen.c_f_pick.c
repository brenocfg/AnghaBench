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
struct pktgen_dev {int curfl; int flags; scalar_t__ lflow; int cflows; TYPE_1__* flows; } ;
struct TYPE_2__ {scalar_t__ count; scalar_t__ flags; } ;

/* Variables and functions */
 int F_FLOW_SEQ ; 
 int random32 () ; 

__attribute__((used)) static inline int f_pick(struct pktgen_dev *pkt_dev)
{
	int flow = pkt_dev->curfl;

	if (pkt_dev->flags & F_FLOW_SEQ) {
		if (pkt_dev->flows[flow].count >= pkt_dev->lflow) {
			/* reset time */
			pkt_dev->flows[flow].count = 0;
			pkt_dev->flows[flow].flags = 0;
			pkt_dev->curfl += 1;
			if (pkt_dev->curfl >= pkt_dev->cflows)
				pkt_dev->curfl = 0; /*reset */
		}
	} else {
		flow = random32() % pkt_dev->cflows;
		pkt_dev->curfl = flow;

		if (pkt_dev->flows[flow].count > pkt_dev->lflow) {
			pkt_dev->flows[flow].count = 0;
			pkt_dev->flows[flow].flags = 0;
		}
	}

	return pkt_dev->curfl;
}