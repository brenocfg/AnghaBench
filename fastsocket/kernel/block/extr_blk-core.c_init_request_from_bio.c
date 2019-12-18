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
struct request {int cmd_flags; int /*<<< orphan*/  q; int /*<<< orphan*/  ioprio; int /*<<< orphan*/  __sector; scalar_t__ errors; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  cpu; } ;
struct bio {int bi_rw; int /*<<< orphan*/  bi_sector; int /*<<< orphan*/  bi_comp_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_RW_AHEAD ; 
 int /*<<< orphan*/  BIO_RW_BARRIER ; 
 int /*<<< orphan*/  BIO_RW_DISCARD ; 
 int /*<<< orphan*/  BIO_RW_FLUSH ; 
 int /*<<< orphan*/  BIO_RW_FUA ; 
 int /*<<< orphan*/  BIO_RW_META ; 
 int /*<<< orphan*/  BIO_RW_NOIDLE ; 
 int /*<<< orphan*/  BIO_RW_SYNCIO ; 
 int REQ_DISCARD ; 
 int REQ_FAILFAST_MASK ; 
 int REQ_FLUSH ; 
 int REQ_FUA ; 
 int REQ_HARDBARRIER ; 
 int REQ_NOIDLE ; 
 int REQ_RW_META ; 
 int REQ_RW_SYNC ; 
 int /*<<< orphan*/  REQ_TYPE_FS ; 
 int /*<<< orphan*/  bio_prio (struct bio*) ; 
 scalar_t__ bio_rw_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_bio_prep (int /*<<< orphan*/ ,struct request*,struct bio*) ; 

void init_request_from_bio(struct request *req, struct bio *bio)
{
	req->cpu = bio->bi_comp_cpu;
	req->cmd_type = REQ_TYPE_FS;

	/*
	 * Inherit FAILFAST from bio (for read-ahead, and explicit
	 * FAILFAST).  FAILFAST flags are identical for req and bio.
	 */
	if (bio_rw_flagged(bio, BIO_RW_AHEAD))
		req->cmd_flags |= REQ_FAILFAST_MASK;
	else
		req->cmd_flags |= bio->bi_rw & REQ_FAILFAST_MASK;

	if (bio_rw_flagged(bio, BIO_RW_DISCARD))
		req->cmd_flags |= REQ_DISCARD;
	if (bio_rw_flagged(bio, BIO_RW_BARRIER))
		req->cmd_flags |= REQ_HARDBARRIER;
	if (bio_rw_flagged(bio, BIO_RW_SYNCIO))
		req->cmd_flags |= REQ_RW_SYNC;
	if (bio_rw_flagged(bio, BIO_RW_META))
		req->cmd_flags |= REQ_RW_META;
	if (bio_rw_flagged(bio, BIO_RW_NOIDLE))
		req->cmd_flags |= REQ_NOIDLE;

	if (bio_rw_flagged(bio, BIO_RW_FLUSH))
		req->cmd_flags |= REQ_FLUSH;
	if (bio_rw_flagged(bio, BIO_RW_FUA))
		req->cmd_flags |= REQ_FUA;

	req->errors = 0;
	req->__sector = bio->bi_sector;
	req->ioprio = bio_prio(bio);
	blk_rq_bio_prep(req->q, req, bio);
}