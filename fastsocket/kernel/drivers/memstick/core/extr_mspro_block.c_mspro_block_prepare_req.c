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
struct request_queue {int dummy; } ;
struct request {scalar_t__ cmd_type; int /*<<< orphan*/  cmd_flags; } ;

/* Variables and functions */
 int BLKPREP_KILL ; 
 int BLKPREP_OK ; 
 int /*<<< orphan*/  REQ_DONTPREP ; 
 scalar_t__ REQ_TYPE_BLOCK_PC ; 
 scalar_t__ REQ_TYPE_FS ; 
 int /*<<< orphan*/  blk_dump_rq_flags (struct request*,char*) ; 

__attribute__((used)) static int mspro_block_prepare_req(struct request_queue *q, struct request *req)
{
	if (req->cmd_type != REQ_TYPE_FS &&
	    req->cmd_type != REQ_TYPE_BLOCK_PC) {
		blk_dump_rq_flags(req, "MSPro unsupported request");
		return BLKPREP_KILL;
	}

	req->cmd_flags |= REQ_DONTPREP;

	return BLKPREP_OK;
}