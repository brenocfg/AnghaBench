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
struct request {scalar_t__ cmd_type; int cmd_flags; int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 scalar_t__ ATAPI_MISC ; 
 scalar_t__ REQ_TYPE_BLOCK_PC ; 
 int REQ_WRITE ; 
 scalar_t__ atapi_cmd_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int atapi_drain_needed(struct request *rq)
{
	if (likely(rq->cmd_type != REQ_TYPE_BLOCK_PC))
		return 0;

	if (!blk_rq_bytes(rq) || (rq->cmd_flags & REQ_WRITE))
		return 0;

	return atapi_cmd_type(rq->cmd[0]) == ATAPI_MISC;
}