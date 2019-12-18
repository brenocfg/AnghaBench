#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mirror_set {int nr_mirrors; struct mirror* mirror; int /*<<< orphan*/  io_client; } ;
struct mirror {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; scalar_t__ bvec; } ;
struct TYPE_6__ {TYPE_2__ ptr; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {struct bio* context; int /*<<< orphan*/  fn; } ;
struct dm_io_request {int bi_rw; TYPE_3__ mem; int /*<<< orphan*/  client; TYPE_1__ notify; } ;
struct dm_io_region {int dummy; } ;
struct bio {int bi_rw; scalar_t__ bi_idx; scalar_t__ bi_io_vec; } ;

/* Variables and functions */
 int BIO_DISCARD ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DM_IO_BVEC ; 
 int /*<<< orphan*/  DM_IO_KMEM ; 
 int WRITE ; 
 int WRITE_FLUSH_FUA ; 
 int /*<<< orphan*/  bio_set_m (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_io (struct dm_io_request*,unsigned int,struct dm_io_region*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_default_mirror (struct mirror_set*) ; 
 int /*<<< orphan*/  map_region (int /*<<< orphan*/ ,struct mirror*,struct bio*) ; 
 int /*<<< orphan*/  write_callback ; 

__attribute__((used)) static void do_write(struct mirror_set *ms, struct bio *bio)
{
	unsigned int i;
	struct dm_io_region io[ms->nr_mirrors], *dest = io;
	struct mirror *m;
	struct dm_io_request io_req = {
		.bi_rw = WRITE | (bio->bi_rw & WRITE_FLUSH_FUA),
		.mem.type = DM_IO_BVEC,
		.mem.ptr.bvec = bio->bi_io_vec + bio->bi_idx,
		.notify.fn = write_callback,
		.notify.context = bio,
		.client = ms->io_client,
	};

	if (bio->bi_rw & BIO_DISCARD) {
		io_req.bi_rw |= BIO_DISCARD;
		io_req.mem.type = DM_IO_KMEM;
		io_req.mem.ptr.addr = NULL;
	}

	for (i = 0, m = ms->mirror; i < ms->nr_mirrors; i++, m++)
		map_region(dest++, m, bio);

	/*
	 * Use default mirror because we only need it to retrieve the reference
	 * to the mirror set in write_callback().
	 */
	bio_set_m(bio, get_default_mirror(ms));

	BUG_ON(dm_io(&io_req, ms->nr_mirrors, io, NULL));
}