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
typedef  int /*<<< orphan*/  u8 ;
struct shash_desc {int /*<<< orphan*/  flags; } ;
struct scatterlist {unsigned int offset; int /*<<< orphan*/  length; } ;
struct hash_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 struct shash_desc** crypto_hash_ctx (int /*<<< orphan*/ ) ; 
 void* crypto_kmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_kunmap (void*,int /*<<< orphan*/ ) ; 
 int crypto_shash_digest (struct shash_desc*,void*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_yield (int /*<<< orphan*/ ) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int shash_compat_final (struct hash_desc*,int /*<<< orphan*/ *) ; 
 int shash_compat_init (struct hash_desc*) ; 
 int shash_compat_update (struct hash_desc*,struct scatterlist*,unsigned int) ; 

__attribute__((used)) static int shash_compat_digest(struct hash_desc *hdesc, struct scatterlist *sg,
			       unsigned int nbytes, u8 *out)
{
	unsigned int offset = sg->offset;
	int err;

	if (nbytes < min(sg->length, ((unsigned int)(PAGE_SIZE)) - offset)) {
		struct shash_desc **descp = crypto_hash_ctx(hdesc->tfm);
		struct shash_desc *desc = *descp;
		void *data;

		desc->flags = hdesc->flags;

		data = crypto_kmap(sg_page(sg), 0);
		err = crypto_shash_digest(desc, data + offset, nbytes, out);
		crypto_kunmap(data, 0);
		crypto_yield(desc->flags);
		goto out;
	}

	err = shash_compat_init(hdesc);
	if (err)
		goto out;

	err = shash_compat_update(hdesc, sg, nbytes);
	if (err)
		goto out;

	err = shash_compat_final(hdesc, out);

out:
	return err;
}