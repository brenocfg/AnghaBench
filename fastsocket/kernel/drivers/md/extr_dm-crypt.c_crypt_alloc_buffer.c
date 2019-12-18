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
struct page {int dummy; } ;
struct dm_crypt_io {TYPE_1__* target; } ;
struct crypt_config {int /*<<< orphan*/  page_pool; int /*<<< orphan*/  bs; } ;
struct bio {int /*<<< orphan*/  bi_size; } ;
typedef  int gfp_t ;
struct TYPE_2__ {struct crypt_config* private; } ;

/* Variables and functions */
 int GFP_NOIO ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int __GFP_HIGHMEM ; 
 int __GFP_NOWARN ; 
 int __GFP_WAIT ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,struct page*,unsigned int,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc_bioset (int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  clone_init (struct dm_crypt_io*,struct bio*) ; 
 struct page* mempool_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mempool_free (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bio *crypt_alloc_buffer(struct dm_crypt_io *io, unsigned size,
				      unsigned *out_of_pages)
{
	struct crypt_config *cc = io->target->private;
	struct bio *clone;
	unsigned int nr_iovecs = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	gfp_t gfp_mask = GFP_NOIO | __GFP_HIGHMEM;
	unsigned i, len;
	struct page *page;

	clone = bio_alloc_bioset(GFP_NOIO, nr_iovecs, cc->bs);
	if (!clone)
		return NULL;

	clone_init(io, clone);
	*out_of_pages = 0;

	for (i = 0; i < nr_iovecs; i++) {
		page = mempool_alloc(cc->page_pool, gfp_mask);
		if (!page) {
			*out_of_pages = 1;
			break;
		}

		/*
		 * If additional pages cannot be allocated without waiting,
		 * return a partially-allocated bio.  The caller will then try
		 * to allocate more bios while submitting this partial bio.
		 */
		gfp_mask = (gfp_mask | __GFP_NOWARN) & ~__GFP_WAIT;

		len = (size > PAGE_SIZE) ? PAGE_SIZE : size;

		if (!bio_add_page(clone, page, len, 0)) {
			mempool_free(page, cc->page_pool);
			break;
		}

		size -= len;
	}

	if (!clone->bi_size) {
		bio_put(clone);
		return NULL;
	}

	return clone;
}