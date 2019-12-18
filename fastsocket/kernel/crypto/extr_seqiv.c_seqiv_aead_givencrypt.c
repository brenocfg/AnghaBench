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
struct seqiv_ctx {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int flags; void* data; int /*<<< orphan*/  complete; } ;
struct aead_request {int /*<<< orphan*/ * iv; int /*<<< orphan*/  assoclen; int /*<<< orphan*/  assoc; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct aead_givcrypt_request {int /*<<< orphan*/  giv; int /*<<< orphan*/  seq; struct aead_request areq; } ;
typedef  int /*<<< orphan*/  crypto_completion_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  aead_geniv_base (struct crypto_aead*) ; 
 struct aead_request* aead_givcrypt_reqctx (struct aead_givcrypt_request*) ; 
 struct crypto_aead* aead_givcrypt_reqtfm (struct aead_givcrypt_request*) ; 
 int /*<<< orphan*/  aead_request_set_assoc (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_aead_alignmask (struct crypto_aead*) ; 
 struct seqiv_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_encrypt (struct aead_request*) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  seqiv_aead_complete ; 
 int /*<<< orphan*/  seqiv_aead_complete2 (struct aead_givcrypt_request*,int) ; 
 int /*<<< orphan*/  seqiv_geniv (struct seqiv_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int seqiv_aead_givencrypt(struct aead_givcrypt_request *req)
{
	struct crypto_aead *geniv = aead_givcrypt_reqtfm(req);
	struct seqiv_ctx *ctx = crypto_aead_ctx(geniv);
	struct aead_request *areq = &req->areq;
	struct aead_request *subreq = aead_givcrypt_reqctx(req);
	crypto_completion_t complete;
	void *data;
	u8 *info;
	unsigned int ivsize;
	int err;

	aead_request_set_tfm(subreq, aead_geniv_base(geniv));

	complete = areq->base.complete;
	data = areq->base.data;
	info = areq->iv;

	ivsize = crypto_aead_ivsize(geniv);

	if (unlikely(!IS_ALIGNED((unsigned long)info,
				 crypto_aead_alignmask(geniv) + 1))) {
		info = kmalloc(ivsize, areq->base.flags &
				       CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL:
								  GFP_ATOMIC);
		if (!info)
			return -ENOMEM;

		complete = seqiv_aead_complete;
		data = req;
	}

	aead_request_set_callback(subreq, areq->base.flags, complete, data);
	aead_request_set_crypt(subreq, areq->src, areq->dst, areq->cryptlen,
			       info);
	aead_request_set_assoc(subreq, areq->assoc, areq->assoclen);

	seqiv_geniv(ctx, info, req->seq, ivsize);
	memcpy(req->giv, info, ivsize);

	err = crypto_aead_encrypt(subreq);
	if (unlikely(info != areq->iv))
		seqiv_aead_complete2(req, err);
	return err;
}