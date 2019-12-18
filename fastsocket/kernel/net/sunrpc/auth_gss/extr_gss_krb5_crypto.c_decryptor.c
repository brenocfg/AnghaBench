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
struct scatterlist {int length; scalar_t__ offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct decryptor_desc {int fraglen; int fragno; int /*<<< orphan*/ * frags; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int crypto_blkcipher_blocksize (int /*<<< orphan*/ ) ; 
 int crypto_blkcipher_decrypt_iv (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_mark_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static int
decryptor(struct scatterlist *sg, void *data)
{
	struct decryptor_desc *desc = data;
	int thislen = desc->fraglen + sg->length;
	int fraglen, ret;

	/* Worst case is 4 fragments: head, end of page 1, start
	 * of page 2, tail.  Anything more is a bug. */
	BUG_ON(desc->fragno > 3);
	sg_set_page(&desc->frags[desc->fragno], sg_page(sg), sg->length,
		    sg->offset);
	desc->fragno++;
	desc->fraglen += sg->length;

	fraglen = thislen & (crypto_blkcipher_blocksize(desc->desc.tfm) - 1);
	thislen -= fraglen;

	if (thislen == 0)
		return 0;

	sg_mark_end(&desc->frags[desc->fragno - 1]);

	ret = crypto_blkcipher_decrypt_iv(&desc->desc, desc->frags,
					  desc->frags, thislen);
	if (ret)
		return ret;

	sg_init_table(desc->frags, 4);

	if (fraglen) {
		sg_set_page(&desc->frags[0], sg_page(sg), fraglen,
				sg->offset + sg->length - fraglen);
		desc->fragno = 1;
		desc->fraglen = fraglen;
	} else {
		desc->fragno = 0;
		desc->fraglen = 0;
	}
	return 0;
}