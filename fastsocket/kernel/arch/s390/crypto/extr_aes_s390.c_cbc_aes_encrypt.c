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
struct scatterlist {int dummy; } ;
struct s390_aes_ctx {int /*<<< orphan*/  iv; int /*<<< orphan*/  enc; int /*<<< orphan*/  key_len; } ;
struct blkcipher_walk {int dummy; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int cbc_aes_crypt (struct blkcipher_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct blkcipher_walk*) ; 
 struct s390_aes_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int fallback_blk_enc (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int /*<<< orphan*/  need_fallback (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cbc_aes_encrypt(struct blkcipher_desc *desc,
			   struct scatterlist *dst, struct scatterlist *src,
			   unsigned int nbytes)
{
	struct s390_aes_ctx *sctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;

	if (unlikely(need_fallback(sctx->key_len)))
		return fallback_blk_enc(desc, dst, src, nbytes);

	blkcipher_walk_init(&walk, dst, src, nbytes);
	return cbc_aes_crypt(desc, sctx->enc, sctx->iv, &walk);
}