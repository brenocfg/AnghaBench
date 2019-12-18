#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mirror {TYPE_4__* ms; } ;
struct TYPE_7__ {struct bio* context; int /*<<< orphan*/  fn; } ;
struct TYPE_5__ {scalar_t__ bvec; } ;
struct TYPE_6__ {TYPE_1__ ptr; int /*<<< orphan*/  type; } ;
struct dm_io_request {int /*<<< orphan*/  client; TYPE_3__ notify; TYPE_2__ mem; int /*<<< orphan*/  bi_rw; } ;
struct dm_io_region {int dummy; } ;
struct bio {scalar_t__ bi_idx; scalar_t__ bi_io_vec; } ;
struct TYPE_8__ {int /*<<< orphan*/  io_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DM_IO_BVEC ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  bio_set_m (struct bio*,struct mirror*) ; 
 int /*<<< orphan*/  dm_io (struct dm_io_request*,int,struct dm_io_region*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_region (struct dm_io_region*,struct mirror*,struct bio*) ; 
 int /*<<< orphan*/  read_callback ; 

__attribute__((used)) static void read_async_bio(struct mirror *m, struct bio *bio)
{
	struct dm_io_region io;
	struct dm_io_request io_req = {
		.bi_rw = READ,
		.mem.type = DM_IO_BVEC,
		.mem.ptr.bvec = bio->bi_io_vec + bio->bi_idx,
		.notify.fn = read_callback,
		.notify.context = bio,
		.client = m->ms->io_client,
	};

	map_region(&io, m, bio);
	bio_set_m(bio, m);
	BUG_ON(dm_io(&io_req, 1, &io, NULL));
}