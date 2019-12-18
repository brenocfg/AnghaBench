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
struct request {unsigned int cmd_flags; } ;

/* Variables and functions */
 unsigned int REQ_FLUSH ; 
 unsigned int REQ_FSEQ_DATA ; 
 unsigned int REQ_FSEQ_POSTFLUSH ; 
 unsigned int REQ_FSEQ_PREFLUSH ; 
 unsigned int REQ_FUA ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 

__attribute__((used)) static unsigned int blk_flush_policy(unsigned int fflags, struct request *rq)
{
	unsigned int policy = 0;

	if (fflags & REQ_FLUSH) {
		if (rq->cmd_flags & REQ_FLUSH)
			policy |= REQ_FSEQ_PREFLUSH;
		if (blk_rq_sectors(rq))
			policy |= REQ_FSEQ_DATA;
		if (!(fflags & REQ_FUA) && (rq->cmd_flags & REQ_FUA))
			policy |= REQ_FSEQ_POSTFLUSH;
	}
	return policy;
}