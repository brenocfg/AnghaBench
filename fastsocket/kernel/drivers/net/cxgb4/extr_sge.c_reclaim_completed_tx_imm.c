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
struct sge_txq {int cidx; int in_use; scalar_t__ size; TYPE_1__* stat; } ;
struct TYPE_2__ {int /*<<< orphan*/  cidx; } ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void reclaim_completed_tx_imm(struct sge_txq *q)
{
	int hw_cidx = ntohs(q->stat->cidx);
	int reclaim = hw_cidx - q->cidx;

	if (reclaim < 0)
		reclaim += q->size;

	q->in_use -= reclaim;
	q->cidx = hw_cidx;
}