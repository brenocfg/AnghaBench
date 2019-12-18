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
struct sge {int dummy; } ;
struct cmdQ {unsigned int processed; unsigned int cleaned; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_cmdQ_buffers (struct sge*,struct cmdQ*,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void reclaim_completed_tx(struct sge *sge, struct cmdQ *q)
{
	unsigned int reclaim = q->processed - q->cleaned;

	if (reclaim) {
		pr_debug("reclaim_completed_tx processed:%d cleaned:%d\n",
			 q->processed, q->cleaned);
		free_cmdQ_buffers(sge, q, reclaim);
		q->cleaned += reclaim;
	}
}