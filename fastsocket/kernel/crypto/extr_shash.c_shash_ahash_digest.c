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
struct shash_desc {int /*<<< orphan*/  flags; } ;
struct scatterlist {unsigned int offset; int /*<<< orphan*/  length; } ;
struct ahash_request {unsigned int nbytes; int /*<<< orphan*/  result; struct scatterlist* src; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 void* crypto_kmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_kunmap (void*,int /*<<< orphan*/ ) ; 
 int crypto_shash_digest (struct shash_desc*,void*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_shash_init (struct shash_desc*) ; 
 int /*<<< orphan*/  crypto_yield (int /*<<< orphan*/ ) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int shash_ahash_finup (struct ahash_request*,struct shash_desc*) ; 

int shash_ahash_digest(struct ahash_request *req, struct shash_desc *desc)
{
	struct scatterlist *sg = req->src;
	unsigned int offset = sg->offset;
	unsigned int nbytes = req->nbytes;
	int err;

	if (nbytes < min(sg->length, ((unsigned int)(PAGE_SIZE)) - offset)) {
		void *data;

		data = crypto_kmap(sg_page(sg), 0);
		err = crypto_shash_digest(desc, data + offset, nbytes,
					  req->result);
		crypto_kunmap(data, 0);
		crypto_yield(desc->flags);
	} else
		err = crypto_shash_init(desc) ?:
		      shash_ahash_finup(req, desc);

	return err;
}