#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pstore {TYPE_2__* store; void* version; void* valid; struct disk_header* header_area; int /*<<< orphan*/  io_client; } ;
struct disk_header {int /*<<< orphan*/  chunk_size; int /*<<< orphan*/  version; int /*<<< orphan*/  valid; int /*<<< orphan*/  magic; } ;
struct TYPE_4__ {int chunk_size; int chunk_mask; scalar_t__ chunk_shift; int /*<<< orphan*/  snap; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,unsigned int,char*) ; 
 int /*<<< orphan*/  DMWARN (char*,...) ; 
 int /*<<< orphan*/  DM_CHUNK_SIZE_DEFAULT_SECTORS ; 
 int ENXIO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ ; 
 void* SNAP_MAGIC ; 
 int alloc_area (struct pstore*) ; 
 int bdev_logical_block_size (int /*<<< orphan*/ ) ; 
 int chunk_io (struct pstore*,struct disk_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dm_exception_store_set_chunk_size (TYPE_2__*,unsigned int,char**) ; 
 int /*<<< orphan*/  dm_io_client_create () ; 
 TYPE_1__* dm_snap_cow (int /*<<< orphan*/ ) ; 
 scalar_t__ ffs (int) ; 
 int /*<<< orphan*/  free_area (struct pstore*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int max (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_header(struct pstore *ps, int *new_snapshot)
{
	int r;
	struct disk_header *dh;
	unsigned chunk_size;
	int chunk_size_supplied = 1;
	char *chunk_err;

	/*
	 * Use default chunk size (or logical_block_size, if larger)
	 * if none supplied
	 */
	if (!ps->store->chunk_size) {
		ps->store->chunk_size = max(DM_CHUNK_SIZE_DEFAULT_SECTORS,
		    bdev_logical_block_size(dm_snap_cow(ps->store->snap)->
					    bdev) >> 9);
		ps->store->chunk_mask = ps->store->chunk_size - 1;
		ps->store->chunk_shift = ffs(ps->store->chunk_size) - 1;
		chunk_size_supplied = 0;
	}

	ps->io_client = dm_io_client_create();
	if (IS_ERR(ps->io_client))
		return PTR_ERR(ps->io_client);

	r = alloc_area(ps);
	if (r)
		return r;

	r = chunk_io(ps, ps->header_area, 0, READ, 1);
	if (r)
		goto bad;

	dh = ps->header_area;

	if (le32_to_cpu(dh->magic) == 0) {
		*new_snapshot = 1;
		return 0;
	}

	if (le32_to_cpu(dh->magic) != SNAP_MAGIC) {
		DMWARN("Invalid or corrupt snapshot");
		r = -ENXIO;
		goto bad;
	}

	*new_snapshot = 0;
	ps->valid = le32_to_cpu(dh->valid);
	ps->version = le32_to_cpu(dh->version);
	chunk_size = le32_to_cpu(dh->chunk_size);

	if (ps->store->chunk_size == chunk_size)
		return 0;

	if (chunk_size_supplied)
		DMWARN("chunk size %u in device metadata overrides "
		       "table chunk size of %u.",
		       chunk_size, ps->store->chunk_size);

	/* We had a bogus chunk_size. Fix stuff up. */
	free_area(ps);

	r = dm_exception_store_set_chunk_size(ps->store, chunk_size,
					      &chunk_err);
	if (r) {
		DMERR("invalid on-disk chunk size %u: %s.",
		      chunk_size, chunk_err);
		return r;
	}

	r = alloc_area(ps);
	return r;

bad:
	free_area(ps);
	return r;
}