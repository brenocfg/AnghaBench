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
struct scatterlist {int offset; int /*<<< orphan*/  length; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  complete; int /*<<< orphan*/  flags; } ;
struct aead_request {unsigned int assoclen; unsigned int cryptlen; TYPE_1__ base; struct scatterlist* assoc; int /*<<< orphan*/ * iv; struct scatterlist* dst; } ;
struct crypto_rfc4543_req_ctx {int /*<<< orphan*/  auth_tag; struct scatterlist* assoc; struct scatterlist* payload; struct scatterlist* cipher; struct aead_request subreq; } ;
struct crypto_rfc4543_ctx {int /*<<< orphan*/  child; int /*<<< orphan*/ * nonce; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * PTR_ALIGN (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  aead_request_set_assoc (struct aead_request*,struct scatterlist*,unsigned int) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,struct scatterlist*,struct scatterlist*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_aead_alignmask (int /*<<< orphan*/ ) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_rfc4543_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_reqsize (int /*<<< orphan*/ ) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 struct crypto_rfc4543_req_ctx* crypto_rfc4543_reqctx (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * page_address (struct page*) ; 
 int /*<<< orphan*/  scatterwalk_crypto_chain (struct scatterlist*,struct scatterlist*,int,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,struct scatterlist*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 struct page* sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct aead_request *crypto_rfc4543_crypt(struct aead_request *req,
						 int enc)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_rfc4543_ctx *ctx = crypto_aead_ctx(aead);
	struct crypto_rfc4543_req_ctx *rctx = crypto_rfc4543_reqctx(req);
	struct aead_request *subreq = &rctx->subreq;
	struct scatterlist *dst = req->dst;
	struct scatterlist *cipher = rctx->cipher;
	struct scatterlist *payload = rctx->payload;
	struct scatterlist *assoc = rctx->assoc;
	unsigned int authsize = crypto_aead_authsize(aead);
	unsigned int assoclen = req->assoclen;
	struct page *dstp;
	u8 *vdst;
	u8 *iv = PTR_ALIGN((u8 *)(rctx + 1) + crypto_aead_reqsize(ctx->child),
			   crypto_aead_alignmask(ctx->child) + 1);

	memcpy(iv, ctx->nonce, 4);
	memcpy(iv + 4, req->iv, 8);

	/* construct cipher/plaintext */
	if (enc)
		memset(rctx->auth_tag, 0, authsize);
	else
		scatterwalk_map_and_copy(rctx->auth_tag, dst,
					 req->cryptlen - authsize,
					 authsize, 0);

	sg_init_one(cipher, rctx->auth_tag, authsize);

	/* construct the aad */
	dstp = sg_page(dst);
	vdst = PageHighMem(dstp) ? NULL : page_address(dstp) + dst->offset;

	sg_init_table(payload, 2);
	sg_set_buf(payload, req->iv, 8);
	scatterwalk_crypto_chain(payload, dst, vdst == req->iv + 8, 2);
	assoclen += 8 + req->cryptlen - (enc ? 0 : authsize);

	sg_init_table(assoc, 2);
	sg_set_page(assoc, sg_page(req->assoc), req->assoc->length,
		    req->assoc->offset);
	scatterwalk_crypto_chain(assoc, payload, 0, 2);

	aead_request_set_tfm(subreq, ctx->child);
	aead_request_set_callback(subreq, req->base.flags, req->base.complete,
				  req->base.data);
	aead_request_set_crypt(subreq, cipher, cipher, enc ? 0 : authsize, iv);
	aead_request_set_assoc(subreq, assoc, assoclen);

	return subreq;
}