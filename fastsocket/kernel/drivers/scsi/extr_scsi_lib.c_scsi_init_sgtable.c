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
struct TYPE_2__ {int nents; int /*<<< orphan*/  sgl; } ;
struct scsi_data_buffer {int /*<<< orphan*/  length; TYPE_1__ table; } ;
struct request {int /*<<< orphan*/  q; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  nr_phys_segments; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int BLKPREP_DEFER ; 
 int BLKPREP_OK ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int blk_rq_map_sg (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_alloc_sgtable (struct scsi_data_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scsi_init_sgtable(struct request *req, struct scsi_data_buffer *sdb,
			     gfp_t gfp_mask)
{
	int count;

	/*
	 * If sg table allocation fails, requeue request later.
	 */
	if (unlikely(scsi_alloc_sgtable(sdb, req->nr_phys_segments,
					gfp_mask))) {
		return BLKPREP_DEFER;
	}

	req->buffer = NULL;

	/* 
	 * Next, walk the list, and fill in the addresses and sizes of
	 * each segment.
	 */
	count = blk_rq_map_sg(req->q, req, sdb->table.sgl);
	BUG_ON(count > sdb->table.nents);
	sdb->table.nents = count;
	sdb->length = blk_rq_bytes(req);
	return BLKPREP_OK;
}