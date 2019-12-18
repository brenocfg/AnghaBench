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
struct request {int cmd_flags; scalar_t__ cmd_type; scalar_t__ rq_disk; } ;

/* Variables and functions */
 int REQ_IO_STAT ; 
 scalar_t__ REQ_TYPE_FS ; 

__attribute__((used)) static inline int blk_do_io_stat(struct request *rq)
{
	return rq->rq_disk &&
	       (rq->cmd_flags & REQ_IO_STAT) &&
		(rq->cmd_type == REQ_TYPE_FS);
}