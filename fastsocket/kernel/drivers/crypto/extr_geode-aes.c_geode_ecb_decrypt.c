#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct geode_aes_op {scalar_t__ keylen; unsigned int len; int /*<<< orphan*/  dir; int /*<<< orphan*/  mode; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; TYPE_4__ dst; TYPE_2__ src; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_DIR_DECRYPT ; 
 scalar_t__ AES_KEYSIZE_128 ; 
 unsigned int AES_MIN_BLOCK_SIZE ; 
 int /*<<< orphan*/  AES_MODE_ECB ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 struct geode_aes_op* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int fallback_blk_dec (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int geode_aes_crypt (struct geode_aes_op*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
geode_ecb_decrypt(struct blkcipher_desc *desc,
		  struct scatterlist *dst, struct scatterlist *src,
		  unsigned int nbytes)
{
	struct geode_aes_op *op = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err, ret;

	if (unlikely(op->keylen != AES_KEYSIZE_128))
		return fallback_blk_dec(desc, dst, src, nbytes);

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while((nbytes = walk.nbytes)) {
		op->src = walk.src.virt.addr,
		op->dst = walk.dst.virt.addr;
		op->mode = AES_MODE_ECB;
		op->len = nbytes - (nbytes % AES_MIN_BLOCK_SIZE);
		op->dir = AES_DIR_DECRYPT;

		ret = geode_aes_crypt(op);
		nbytes -= ret;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}