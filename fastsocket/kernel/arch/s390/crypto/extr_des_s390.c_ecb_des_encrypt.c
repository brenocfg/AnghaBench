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
struct crypt_s390_des_ctx {int /*<<< orphan*/  key; } ;
struct blkcipher_walk {int dummy; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_DEA_ENCRYPT ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 struct crypt_s390_des_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int ecb_desall_crypt (struct blkcipher_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct blkcipher_walk*) ; 

__attribute__((used)) static int ecb_des_encrypt(struct blkcipher_desc *desc,
			   struct scatterlist *dst, struct scatterlist *src,
			   unsigned int nbytes)
{
	struct crypt_s390_des_ctx *sctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	return ecb_desall_crypt(desc, KM_DEA_ENCRYPT, sctx->key, &walk);
}