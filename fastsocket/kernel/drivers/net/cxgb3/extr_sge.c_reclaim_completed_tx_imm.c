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
struct sge_txq {unsigned int processed; unsigned int cleaned; unsigned int in_use; } ;

/* Variables and functions */

__attribute__((used)) static inline void reclaim_completed_tx_imm(struct sge_txq *q)
{
	unsigned int reclaim = q->processed - q->cleaned;

	q->in_use -= reclaim;
	q->cleaned += reclaim;
}