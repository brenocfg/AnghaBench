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
typedef  int /*<<< orphan*/  u8 ;
struct dm_crypt_request {int /*<<< orphan*/  sg_out; int /*<<< orphan*/  sg_in; struct convert_context* ctx; } ;
struct crypt_config {TYPE_1__* iv_gen_ops; int /*<<< orphan*/  tfm; } ;
struct convert_context {scalar_t__ offset_in; scalar_t__ offset_out; int /*<<< orphan*/  bio_in; int /*<<< orphan*/  sector; int /*<<< orphan*/  idx_out; int /*<<< orphan*/  idx_in; int /*<<< orphan*/  bio_out; } ;
struct bio_vec {scalar_t__ bv_offset; scalar_t__ bv_len; int /*<<< orphan*/  bv_page; } ;
struct ablkcipher_request {int dummy; } ;
struct TYPE_2__ {int (* generator ) (struct crypt_config*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,scalar_t__) ; 
 int SECTOR_SHIFT ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  ablkcipher_request_set_crypt (struct ablkcipher_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bio_data_dir (int /*<<< orphan*/ ) ; 
 struct bio_vec* bio_iovec_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ablkcipher_alignmask (int /*<<< orphan*/ ) ; 
 int crypto_ablkcipher_decrypt (struct ablkcipher_request*) ; 
 int crypto_ablkcipher_encrypt (struct ablkcipher_request*) ; 
 struct dm_crypt_request* dmreq_of_req (struct crypt_config*,struct ablkcipher_request*) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int stub1 (struct crypt_config*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypt_convert_block(struct crypt_config *cc,
			       struct convert_context *ctx,
			       struct ablkcipher_request *req)
{
	struct bio_vec *bv_in = bio_iovec_idx(ctx->bio_in, ctx->idx_in);
	struct bio_vec *bv_out = bio_iovec_idx(ctx->bio_out, ctx->idx_out);
	struct dm_crypt_request *dmreq;
	u8 *iv;
	int r = 0;

	dmreq = dmreq_of_req(cc, req);
	iv = (u8 *)ALIGN((unsigned long)(dmreq + 1),
			 crypto_ablkcipher_alignmask(cc->tfm) + 1);

	dmreq->ctx = ctx;
	sg_init_table(&dmreq->sg_in, 1);
	sg_set_page(&dmreq->sg_in, bv_in->bv_page, 1 << SECTOR_SHIFT,
		    bv_in->bv_offset + ctx->offset_in);

	sg_init_table(&dmreq->sg_out, 1);
	sg_set_page(&dmreq->sg_out, bv_out->bv_page, 1 << SECTOR_SHIFT,
		    bv_out->bv_offset + ctx->offset_out);

	ctx->offset_in += 1 << SECTOR_SHIFT;
	if (ctx->offset_in >= bv_in->bv_len) {
		ctx->offset_in = 0;
		ctx->idx_in++;
	}

	ctx->offset_out += 1 << SECTOR_SHIFT;
	if (ctx->offset_out >= bv_out->bv_len) {
		ctx->offset_out = 0;
		ctx->idx_out++;
	}

	if (cc->iv_gen_ops) {
		r = cc->iv_gen_ops->generator(cc, iv, ctx->sector);
		if (r < 0)
			return r;
	}

	ablkcipher_request_set_crypt(req, &dmreq->sg_in, &dmreq->sg_out,
				     1 << SECTOR_SHIFT, iv);

	if (bio_data_dir(ctx->bio_in) == WRITE)
		r = crypto_ablkcipher_encrypt(req);
	else
		r = crypto_ablkcipher_decrypt(req);

	return r;
}