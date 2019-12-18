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
struct scatterlist {int dummy; } ;
struct crypto_cipher {int dummy; } ;
struct crypto_ccm_req_priv_ctx {scalar_t__ ilen; int /*<<< orphan*/ * idata; int /*<<< orphan*/ * odata; } ;
struct crypto_ccm_ctx {struct crypto_cipher* cipher; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {unsigned int assoclen; struct scatterlist* assoc; } ;

/* Variables and functions */
 struct crypto_ccm_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 struct crypto_ccm_req_priv_ctx* crypto_ccm_reqctx (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (struct crypto_cipher*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ format_adata (int /*<<< orphan*/ *,unsigned int) ; 
 int format_input (int /*<<< orphan*/ *,struct aead_request*,unsigned int) ; 
 int /*<<< orphan*/  get_data_to_compute (struct crypto_cipher*,struct crypto_ccm_req_priv_ctx*,struct scatterlist*,unsigned int) ; 

__attribute__((used)) static int crypto_ccm_auth(struct aead_request *req, struct scatterlist *plain,
			   unsigned int cryptlen)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_ccm_ctx *ctx = crypto_aead_ctx(aead);
	struct crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	struct crypto_cipher *cipher = ctx->cipher;
	unsigned int assoclen = req->assoclen;
	u8 *odata = pctx->odata;
	u8 *idata = pctx->idata;
	int err;

	/* format control data for input */
	err = format_input(odata, req, cryptlen);
	if (err)
		goto out;

	/* encrypt first block to use as start in computing mac  */
	crypto_cipher_encrypt_one(cipher, odata, odata);

	/* format associated data and compute into mac */
	if (assoclen) {
		pctx->ilen = format_adata(idata, assoclen);
		get_data_to_compute(cipher, pctx, req->assoc, req->assoclen);
	} else {
		pctx->ilen = 0;
	}

	/* compute plaintext into mac */
	get_data_to_compute(cipher, pctx, plain, cryptlen);

out:
	return err;
}