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
struct io {int dummy; } ;
struct dpages {int dummy; } ;
struct dm_io_region {scalar_t__ count; } ;

/* Variables and functions */
 int BIO_FLUSH ; 
 int BIO_RW_SYNCIO ; 
 int BIO_RW_UNPLUG ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int DM_IO_MAX_REGIONS ; 
 int /*<<< orphan*/  dec_count (struct io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_region (int,int,struct dm_io_region*,struct dpages*,struct io*) ; 

__attribute__((used)) static void dispatch_io(int rw, unsigned int num_regions,
			struct dm_io_region *where, struct dpages *dp,
			struct io *io, int sync)
{
	int i;
	struct dpages old_pages = *dp;

	BUG_ON(num_regions > DM_IO_MAX_REGIONS);

	if (sync)
		rw |= (1 << BIO_RW_SYNCIO) | (1 << BIO_RW_UNPLUG);

	/*
	 * For multiple regions we need to be careful to rewind
	 * the dp object for each call to do_region.
	 */
	for (i = 0; i < num_regions; i++) {
		*dp = old_pages;
		if (where[i].count || (rw & BIO_FLUSH))
			do_region(rw, i, where + i, dp, io);
	}

	/*
	 * Drop the extra reference that we were holding to avoid
	 * the io being completed too early.
	 */
	dec_count(io, 0, 0);
}