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
struct crypt_config {int /*<<< orphan*/  page_pool; } ;
struct bio_vec {int /*<<< orphan*/ * bv_page; } ;
struct bio {unsigned int bi_vcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct bio_vec* bio_iovec_idx (struct bio*,unsigned int) ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypt_free_buffer_pages(struct crypt_config *cc, struct bio *clone)
{
	unsigned int i;
	struct bio_vec *bv;

	for (i = 0; i < clone->bi_vcnt; i++) {
		bv = bio_iovec_idx(clone, i);
		BUG_ON(!bv->bv_page);
		mempool_free(bv->bv_page, cc->page_pool);
		bv->bv_page = NULL;
	}
}