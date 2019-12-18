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
struct request {int /*<<< orphan*/  q; struct dm_rq_target_io* end_io_data; } ;
struct mapped_device {int dummy; } ;
struct dm_target {TYPE_1__* type; } ;
struct dm_rq_target_io {int /*<<< orphan*/  orig; int /*<<< orphan*/  info; struct dm_target* ti; } ;
struct TYPE_2__ {int (* map_rq ) (struct dm_target*,struct request*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DMWARN (char*,int) ; 
#define  DM_MAPIO_REMAPPED 130 
#define  DM_MAPIO_REQUEUE 129 
#define  DM_MAPIO_SUBMITTED 128 
 int /*<<< orphan*/  blk_rq_pos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_disk (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_dispatch_request (struct request*) ; 
 int /*<<< orphan*/  dm_kill_unmapped_request (struct request*,int) ; 
 int /*<<< orphan*/  dm_requeue_unmapped_request (struct request*) ; 
 int stub1 (struct dm_target*,struct request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_block_rq_remap (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int map_request(struct dm_target *ti, struct request *clone,
		       struct mapped_device *md)
{
	int r, requeued = 0;
	struct dm_rq_target_io *tio = clone->end_io_data;

	tio->ti = ti;
	r = ti->type->map_rq(ti, clone, &tio->info);
	switch (r) {
	case DM_MAPIO_SUBMITTED:
		/* The target has taken the I/O to submit by itself later */
		break;
	case DM_MAPIO_REMAPPED:
		/* The target has remapped the I/O so dispatch it */
		trace_block_rq_remap(clone->q, clone, disk_devt(dm_disk(md)),
				     blk_rq_pos(tio->orig));
		dm_dispatch_request(clone);
		break;
	case DM_MAPIO_REQUEUE:
		/* The target wants to requeue the I/O */
		dm_requeue_unmapped_request(clone);
		requeued = 1;
		break;
	default:
		if (r > 0) {
			DMWARN("unimplemented target map return value: %d", r);
			BUG();
		}

		/* The target wants to complete the I/O */
		dm_kill_unmapped_request(clone, r);
		break;
	}

	return requeued;
}