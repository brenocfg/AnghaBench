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
typedef  int u8 ;
struct scatterlist {int dummy; } ;
struct TYPE_3__ {int* iv; } ;
struct TYPE_4__ {TYPE_1__ ctr; } ;
struct nx_crypto_ctx {TYPE_2__ priv; } ;
struct blkcipher_desc {int* info; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR_RFC3686_IV_SIZE ; 
 int CTR_RFC3686_NONCE_SIZE ; 
 struct nx_crypto_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int ctr_aes_nx_crypt (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctr3686_aes_nx_crypt(struct blkcipher_desc *desc,
				struct scatterlist    *dst,
				struct scatterlist    *src,
				unsigned int           nbytes)
{
	struct nx_crypto_ctx *nx_ctx = crypto_blkcipher_ctx(desc->tfm);
	u8 *iv = nx_ctx->priv.ctr.iv;

	memcpy(iv + CTR_RFC3686_NONCE_SIZE,
	       desc->info, CTR_RFC3686_IV_SIZE);
	iv[15] = 1;

	desc->info = nx_ctx->priv.ctr.iv;

	return ctr_aes_nx_crypt(desc, dst, src, nbytes);
}