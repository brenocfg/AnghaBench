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
typedef  int /*<<< orphan*/  u32 ;
struct zram {int /*<<< orphan*/  lock; } ;
struct bio_vec {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int READ ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int zram_bvec_read (struct zram*,struct bio_vec*,int /*<<< orphan*/ ,int,struct bio*) ; 
 int zram_bvec_write (struct zram*,struct bio_vec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zram_bvec_rw(struct zram *zram, struct bio_vec *bvec, u32 index,
			int offset, struct bio *bio, int rw)
{
	int ret;

	if (rw == READ) {
		down_read(&zram->lock);
		ret = zram_bvec_read(zram, bvec, index, offset, bio);
		up_read(&zram->lock);
	} else {
		down_write(&zram->lock);
		ret = zram_bvec_write(zram, bvec, index, offset);
		up_write(&zram->lock);
	}

	return ret;
}