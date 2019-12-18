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
typedef  int u8 ;
struct scatterlist {int dummy; } ;
struct ablkcipher_request {int dummy; } ;
struct crypto_ccm_req_priv_ctx {int* odata; struct scatterlist* src; int /*<<< orphan*/  flags; struct scatterlist* dst; struct ablkcipher_request abreq; } ;
struct crypto_ccm_ctx {int /*<<< orphan*/  ctr; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {unsigned int cryptlen; int* iv; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  ablkcipher_request_set_callback (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ablkcipher_request_set_crypt (struct ablkcipher_request*,struct scatterlist*,struct scatterlist*,unsigned int,int*) ; 
 int /*<<< orphan*/  ablkcipher_request_set_tfm (struct ablkcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 int crypto_ablkcipher_encrypt (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_ccm_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_ccm_auth (struct aead_request*,int /*<<< orphan*/ ,unsigned int) ; 
 int crypto_ccm_check_iv (int*) ; 
 int /*<<< orphan*/  crypto_ccm_encrypt_done ; 
 struct crypto_ccm_req_priv_ctx* crypto_ccm_reqctx (struct aead_request*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_sg_chain (struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int*,int) ; 

__attribute__((used)) static int crypto_ccm_encrypt(struct aead_request *req)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_ccm_ctx *ctx = crypto_aead_ctx(aead);
	struct crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	struct ablkcipher_request *abreq = &pctx->abreq;
	struct scatterlist *dst;
	unsigned int cryptlen = req->cryptlen;
	u8 *odata = pctx->odata;
	u8 *iv = req->iv;
	int err;

	err = crypto_ccm_check_iv(iv);
	if (err)
		return err;

	pctx->flags = aead_request_flags(req);

	err = crypto_ccm_auth(req, req->src, cryptlen);
	if (err)
		return err;

	 /* Note: rfc 3610 and NIST 800-38C require counter of
	 * zero to encrypt auth tag.
	 */
	memset(iv + 15 - iv[0], 0, iv[0] + 1);

	sg_init_table(pctx->src, 2);
	sg_set_buf(pctx->src, odata, 16);
	scatterwalk_sg_chain(pctx->src, 2, req->src);

	dst = pctx->src;
	if (req->src != req->dst) {
		sg_init_table(pctx->dst, 2);
		sg_set_buf(pctx->dst, odata, 16);
		scatterwalk_sg_chain(pctx->dst, 2, req->dst);
		dst = pctx->dst;
	}

	ablkcipher_request_set_tfm(abreq, ctx->ctr);
	ablkcipher_request_set_callback(abreq, pctx->flags,
					crypto_ccm_encrypt_done, req);
	ablkcipher_request_set_crypt(abreq, pctx->src, dst, cryptlen + 16, iv);
	err = crypto_ablkcipher_encrypt(abreq);
	if (err)
		return err;

	/* copy authtag to end of dst */
	scatterwalk_map_and_copy(odata, req->dst, cryptlen,
				 crypto_aead_authsize(aead), 1);
	return err;
}