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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  flags; void* data; int /*<<< orphan*/  complete; } ;
struct TYPE_4__ {int /*<<< orphan*/ * info; scalar_t__ nbytes; TYPE_1__ base; struct scatterlist* dst; struct scatterlist* src; } ;
struct skcipher_givcrypt_request {int /*<<< orphan*/ * giv; int /*<<< orphan*/  seq; TYPE_2__ creq; } ;
struct scatterlist {int offset; } ;
struct page {int dummy; } ;
struct eseqiv_request_ctx {struct scatterlist* src; struct scatterlist* dst; scalar_t__ tail; } ;
struct eseqiv_ctx {int /*<<< orphan*/ * salt; scalar_t__ reqoff; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int dummy; } ;
typedef  int /*<<< orphan*/  crypto_completion_t ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/ * PTR_ALIGN (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  ablkcipher_request_set_callback (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ablkcipher_request_set_crypt (struct ablkcipher_request*,struct scatterlist*,struct scatterlist*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ablkcipher_request_set_tfm (struct ablkcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ablkcipher_alignmask (struct crypto_ablkcipher*) ; 
 struct eseqiv_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int crypto_ablkcipher_encrypt (struct ablkcipher_request*) ; 
 unsigned int crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  eseqiv_complete ; 
 int /*<<< orphan*/  eseqiv_complete2 (struct skcipher_givcrypt_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * page_address (struct page*) ; 
 int /*<<< orphan*/  scatterwalk_crypto_chain (struct scatterlist*,struct scatterlist*,int,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 struct page* sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  skcipher_geniv_cipher (struct crypto_ablkcipher*) ; 
 struct eseqiv_request_ctx* skcipher_givcrypt_reqctx (struct skcipher_givcrypt_request*) ; 
 struct crypto_ablkcipher* skcipher_givcrypt_reqtfm (struct skcipher_givcrypt_request*) ; 

__attribute__((used)) static int eseqiv_givencrypt(struct skcipher_givcrypt_request *req)
{
	struct crypto_ablkcipher *geniv = skcipher_givcrypt_reqtfm(req);
	struct eseqiv_ctx *ctx = crypto_ablkcipher_ctx(geniv);
	struct eseqiv_request_ctx *reqctx = skcipher_givcrypt_reqctx(req);
	struct ablkcipher_request *subreq;
	crypto_completion_t complete;
	void *data;
	struct scatterlist *osrc, *odst;
	struct scatterlist *dst;
	struct page *srcp;
	struct page *dstp;
	u8 *giv;
	u8 *vsrc;
	u8 *vdst;
	__be64 seq;
	unsigned int ivsize;
	unsigned int len;
	int err;

	subreq = (void *)(reqctx->tail + ctx->reqoff);
	ablkcipher_request_set_tfm(subreq, skcipher_geniv_cipher(geniv));

	giv = req->giv;
	complete = req->creq.base.complete;
	data = req->creq.base.data;

	osrc = req->creq.src;
	odst = req->creq.dst;
	srcp = sg_page(osrc);
	dstp = sg_page(odst);
	vsrc = PageHighMem(srcp) ? NULL : page_address(srcp) + osrc->offset;
	vdst = PageHighMem(dstp) ? NULL : page_address(dstp) + odst->offset;

	ivsize = crypto_ablkcipher_ivsize(geniv);

	if (vsrc != giv + ivsize && vdst != giv + ivsize) {
		giv = PTR_ALIGN((u8 *)reqctx->tail,
				crypto_ablkcipher_alignmask(geniv) + 1);
		complete = eseqiv_complete;
		data = req;
	}

	ablkcipher_request_set_callback(subreq, req->creq.base.flags, complete,
					data);

	sg_init_table(reqctx->src, 2);
	sg_set_buf(reqctx->src, giv, ivsize);
	scatterwalk_crypto_chain(reqctx->src, osrc, vsrc == giv + ivsize, 2);

	dst = reqctx->src;
	if (osrc != odst) {
		sg_init_table(reqctx->dst, 2);
		sg_set_buf(reqctx->dst, giv, ivsize);
		scatterwalk_crypto_chain(reqctx->dst, odst, vdst == giv + ivsize, 2);

		dst = reqctx->dst;
	}

	ablkcipher_request_set_crypt(subreq, reqctx->src, dst,
				     req->creq.nbytes + ivsize,
				     req->creq.info);

	memcpy(req->creq.info, ctx->salt, ivsize);

	len = ivsize;
	if (ivsize > sizeof(u64)) {
		memset(req->giv, 0, ivsize - sizeof(u64));
		len = sizeof(u64);
	}
	seq = cpu_to_be64(req->seq);
	memcpy(req->giv + ivsize - len, &seq, len);

	err = crypto_ablkcipher_encrypt(subreq);
	if (err)
		goto out;

	if (giv != req->giv)
		eseqiv_complete2(req);

out:
	return err;
}