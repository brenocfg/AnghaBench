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
struct crypto_gcm_req_priv_ctx {struct scatterlist* src; struct scatterlist* dst; int /*<<< orphan*/  auth_tag; } ;
struct crypto_gcm_ctx {int /*<<< orphan*/  ctr; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  iv; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct ablkcipher_request {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ablkcipher_request_set_crypt (struct ablkcipher_request*,struct scatterlist*,struct scatterlist*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ablkcipher_request_set_tfm (struct ablkcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct crypto_gcm_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_sg_chain (struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void crypto_gcm_init_crypt(struct ablkcipher_request *ablk_req,
				  struct aead_request *req,
				  unsigned int cryptlen)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_gcm_ctx *ctx = crypto_aead_ctx(aead);
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	struct scatterlist *dst;
	__be32 counter = cpu_to_be32(1);

	memset(pctx->auth_tag, 0, sizeof(pctx->auth_tag));
	memcpy(req->iv + 12, &counter, 4);

	sg_init_table(pctx->src, 2);
	sg_set_buf(pctx->src, pctx->auth_tag, sizeof(pctx->auth_tag));
	scatterwalk_sg_chain(pctx->src, 2, req->src);

	dst = pctx->src;
	if (req->src != req->dst) {
		sg_init_table(pctx->dst, 2);
		sg_set_buf(pctx->dst, pctx->auth_tag, sizeof(pctx->auth_tag));
		scatterwalk_sg_chain(pctx->dst, 2, req->dst);
		dst = pctx->dst;
	}

	ablkcipher_request_set_tfm(ablk_req, ctx->ctr);
	ablkcipher_request_set_crypt(ablk_req, pctx->src, dst,
				     cryptlen + sizeof(pctx->auth_tag),
				     req->iv);
}