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
struct super_block {int s_blocksize; int /*<<< orphan*/  s_bdev; } ;
struct page {int dummy; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_sb; struct super_block* sd_vfs; } ;
struct gfs2_sb {int dummy; } ;
struct bio {int bi_sector; struct page* bi_private; int /*<<< orphan*/  bi_end_io; int /*<<< orphan*/  bi_bdev; } ;
typedef  int sector_t ;

/* Variables and functions */
 int BIO_RW_META ; 
 int /*<<< orphan*/  ClearPageDirty (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int EIO ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int READ_SYNC ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  end_bio_io_page ; 
 int /*<<< orphan*/  gfs2_sb_in (int /*<<< orphan*/ *,struct gfs2_sb*) ; 
 struct gfs2_sb* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  submit_bio (int,struct bio*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_on_page_locked (struct page*) ; 

__attribute__((used)) static int gfs2_read_super(struct gfs2_sbd *sdp, sector_t sector)
{
	struct super_block *sb = sdp->sd_vfs;
	struct gfs2_sb *p;
	struct page *page;
	struct bio *bio;

	page = alloc_page(GFP_NOFS);
	if (unlikely(!page))
		return -ENOBUFS;

	ClearPageUptodate(page);
	ClearPageDirty(page);
	lock_page(page);

	bio = bio_alloc(GFP_NOFS, 1);
	bio->bi_sector = sector * (sb->s_blocksize >> 9);
	bio->bi_bdev = sb->s_bdev;
	bio_add_page(bio, page, PAGE_SIZE, 0);

	bio->bi_end_io = end_bio_io_page;
	bio->bi_private = page;
	submit_bio(READ_SYNC | (1 << BIO_RW_META), bio);
	wait_on_page_locked(page);
	bio_put(bio);
	if (!PageUptodate(page)) {
		__free_page(page);
		return -EIO;
	}
	p = kmap(page);
	gfs2_sb_in(&sdp->sd_sb, p);
	kunmap(page);
	__free_page(page);
	return 0;
}