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
struct scatterlist {unsigned int offset; unsigned int length; } ;
struct page {int dummy; } ;
struct hash_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;
struct crypto_tfm {TYPE_2__* __crt_alg; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dia_update ) (struct crypto_tfm*,char*,unsigned int) ;} ;
struct TYPE_4__ {TYPE_1__ cra_digest; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 struct crypto_tfm* crypto_hash_tfm (int /*<<< orphan*/ ) ; 
 char* crypto_kmap (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_kunmap (char*,int /*<<< orphan*/ ) ; 
 unsigned int crypto_tfm_alg_alignmask (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_yield (int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 struct scatterlist* scatterwalk_sg_next (struct scatterlist*) ; 
 struct page* sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  stub1 (struct crypto_tfm*,char*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct crypto_tfm*,char*,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static int update2(struct hash_desc *desc,
		   struct scatterlist *sg, unsigned int nbytes)
{
	struct crypto_tfm *tfm = crypto_hash_tfm(desc->tfm);
	unsigned int alignmask = crypto_tfm_alg_alignmask(tfm);

	if (!nbytes)
		return 0;

	for (;;) {
		struct page *pg = sg_page(sg);
		unsigned int offset = sg->offset;
		unsigned int l = sg->length;

		if (unlikely(l > nbytes))
			l = nbytes;
		nbytes -= l;

		do {
			unsigned int bytes_from_page = min(l, ((unsigned int)
							   (PAGE_SIZE)) - 
							   offset);
			char *src = crypto_kmap(pg, 0);
			char *p = src + offset;

			if (unlikely(offset & alignmask)) {
				unsigned int bytes =
					alignmask + 1 - (offset & alignmask);
				bytes = min(bytes, bytes_from_page);
				tfm->__crt_alg->cra_digest.dia_update(tfm, p,
								      bytes);
				p += bytes;
				bytes_from_page -= bytes;
				l -= bytes;
			}
			tfm->__crt_alg->cra_digest.dia_update(tfm, p,
							      bytes_from_page);
			crypto_kunmap(src, 0);
			crypto_yield(desc->flags);
			offset = 0;
			pg++;
			l -= bytes_from_page;
		} while (l > 0);

		if (!nbytes)
			break;
		sg = scatterwalk_sg_next(sg);
	}

	return 0;
}