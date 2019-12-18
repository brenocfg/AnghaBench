#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pstore {int /*<<< orphan*/  metadata_wq; int /*<<< orphan*/  io_client; TYPE_1__* store; } ;
struct mdata_req {int result; int /*<<< orphan*/  work; struct dm_io_request* io_req; struct dm_io_region* where; } ;
struct TYPE_9__ {int /*<<< orphan*/ * fn; } ;
struct TYPE_7__ {void* vma; } ;
struct TYPE_8__ {TYPE_2__ ptr; int /*<<< orphan*/  type; } ;
struct dm_io_request {int bi_rw; TYPE_4__ notify; int /*<<< orphan*/  client; TYPE_3__ mem; } ;
struct dm_io_region {int sector; int count; int /*<<< orphan*/  bdev; } ;
typedef  int chunk_t ;
struct TYPE_10__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_6__ {int chunk_size; int /*<<< orphan*/  snap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_IO_VMA ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dm_io (struct dm_io_request*,int,struct dm_io_region*,int /*<<< orphan*/ *) ; 
 TYPE_5__* dm_snap_cow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_metadata ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chunk_io(struct pstore *ps, void *area, chunk_t chunk, int rw,
		    int metadata)
{
	struct dm_io_region where = {
		.bdev = dm_snap_cow(ps->store->snap)->bdev,
		.sector = ps->store->chunk_size * chunk,
		.count = ps->store->chunk_size,
	};
	struct dm_io_request io_req = {
		.bi_rw = rw,
		.mem.type = DM_IO_VMA,
		.mem.ptr.vma = area,
		.client = ps->io_client,
		.notify.fn = NULL,
	};
	struct mdata_req req;

	if (!metadata)
		return dm_io(&io_req, 1, &where, NULL);

	req.where = &where;
	req.io_req = &io_req;

	/*
	 * Issue the synchronous I/O from a different thread
	 * to avoid generic_make_request recursion.
	 */
	INIT_WORK(&req.work, do_metadata);
	queue_work(ps->metadata_wq, &req.work);
	flush_workqueue(ps->metadata_wq);

	return req.result;
}