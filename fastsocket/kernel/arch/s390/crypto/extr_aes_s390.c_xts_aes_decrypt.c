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
struct s390_xts_ctx {int key_len; int /*<<< orphan*/  dec; } ;
struct blkcipher_walk {int dummy; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 struct s390_xts_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int xts_aes_crypt (struct blkcipher_desc*,int /*<<< orphan*/ ,struct s390_xts_ctx*,struct blkcipher_walk*) ; 
 int xts_fallback_decrypt (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,unsigned int) ; 

__attribute__((used)) static int xts_aes_decrypt(struct blkcipher_desc *desc,
			   struct scatterlist *dst, struct scatterlist *src,
			   unsigned int nbytes)
{
	struct s390_xts_ctx *xts_ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;

	if (unlikely(xts_ctx->key_len == 48))
		return xts_fallback_decrypt(desc, dst, src, nbytes);

	blkcipher_walk_init(&walk, dst, src, nbytes);
	return xts_aes_crypt(desc, xts_ctx->dec, xts_ctx, &walk);
}