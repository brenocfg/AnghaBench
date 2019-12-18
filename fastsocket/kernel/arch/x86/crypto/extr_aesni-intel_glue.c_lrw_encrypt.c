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
struct lrw_crypt_req {int tbuflen; int /*<<< orphan*/  crypt_fn; int /*<<< orphan*/  crypt_ctx; int /*<<< orphan*/ * table_ctx; int /*<<< orphan*/ * tbuf; } ;
struct blkcipher_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;
struct aesni_lrw_ctx {int /*<<< orphan*/  raw_aes_ctx; int /*<<< orphan*/  lrw_table; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  be128 ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  aes_ctx (int /*<<< orphan*/ ) ; 
 struct aesni_lrw_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 
 int lrw_crypt (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,unsigned int,struct lrw_crypt_req*) ; 
 int /*<<< orphan*/  lrw_xts_encrypt_callback ; 

__attribute__((used)) static int lrw_encrypt(struct blkcipher_desc *desc, struct scatterlist *dst,
		       struct scatterlist *src, unsigned int nbytes)
{
	struct aesni_lrw_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	be128 buf[8];
	struct lrw_crypt_req req = {
		.tbuf = buf,
		.tbuflen = sizeof(buf),

		.table_ctx = &ctx->lrw_table,
		.crypt_ctx = aes_ctx(ctx->raw_aes_ctx),
		.crypt_fn = lrw_xts_encrypt_callback,
	};
	int ret;

	desc->flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;

	kernel_fpu_begin();
	ret = lrw_crypt(desc, dst, src, nbytes, &req);
	kernel_fpu_end();

	return ret;
}