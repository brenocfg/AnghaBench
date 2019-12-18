#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bi_sector; int /*<<< orphan*/ * bi_end_io; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_max_vecs; int /*<<< orphan*/  bi_io_vec; } ;
struct dm_buffer {char* data; TYPE_2__ bio; TYPE_1__* c; int /*<<< orphan*/  bio_vec; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  bio_end_io_t ;
struct TYPE_5__ {int sectors_per_block_bits; int block_size; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DM_BUFIO_INLINE_VECS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bio_add_page (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bio_init (TYPE_2__*) ; 
 int /*<<< orphan*/  submit_bio (int,TYPE_2__*) ; 
 int /*<<< orphan*/  use_dmio (struct dm_buffer*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_page (char*) ; 
 int virt_to_phys (char*) ; 

__attribute__((used)) static void use_inline_bio(struct dm_buffer *b, int rw, sector_t block,
			   bio_end_io_t *end_io)
{
	char *ptr;
	int len;

	bio_init(&b->bio);
	b->bio.bi_io_vec = b->bio_vec;
	b->bio.bi_max_vecs = DM_BUFIO_INLINE_VECS;
	b->bio.bi_sector = block << b->c->sectors_per_block_bits;
	b->bio.bi_bdev = b->c->bdev;
	b->bio.bi_end_io = end_io;

	/*
	 * We assume that if len >= PAGE_SIZE ptr is page-aligned.
	 * If len < PAGE_SIZE the buffer doesn't cross page boundary.
	 */
	ptr = b->data;
	len = b->c->block_size;

	if (len >= PAGE_SIZE)
		BUG_ON((unsigned long)ptr & (PAGE_SIZE - 1));
	else
		BUG_ON((unsigned long)ptr & (len - 1));

	do {
		if (!bio_add_page(&b->bio, virt_to_page(ptr),
				  len < PAGE_SIZE ? len : PAGE_SIZE,
				  virt_to_phys(ptr) & (PAGE_SIZE - 1))) {
			BUG_ON(b->c->block_size <= PAGE_SIZE);
			use_dmio(b, rw, block, end_io);
			return;
		}

		len -= PAGE_SIZE;
		ptr += PAGE_SIZE;
	} while (len > 0);

	submit_bio(rw, &b->bio);
}