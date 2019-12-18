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
struct TYPE_3__ {int flags; void* data; int /*<<< orphan*/  complete; } ;
struct TYPE_4__ {int /*<<< orphan*/ * info; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct skcipher_givcrypt_request {TYPE_2__ creq; int /*<<< orphan*/  giv; int /*<<< orphan*/  seq; } ;
struct seqiv_ctx {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int dummy; } ;
typedef  int /*<<< orphan*/  crypto_completion_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  ablkcipher_request_set_callback (struct ablkcipher_request*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ablkcipher_request_set_crypt (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ablkcipher_request_set_tfm (struct ablkcipher_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ablkcipher_alignmask (struct crypto_ablkcipher*) ; 
 struct seqiv_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int crypto_ablkcipher_encrypt (struct ablkcipher_request*) ; 
 unsigned int crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  seqiv_complete ; 
 int /*<<< orphan*/  seqiv_complete2 (struct skcipher_givcrypt_request*,int) ; 
 int /*<<< orphan*/  seqiv_geniv (struct seqiv_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skcipher_geniv_cipher (struct crypto_ablkcipher*) ; 
 struct ablkcipher_request* skcipher_givcrypt_reqctx (struct skcipher_givcrypt_request*) ; 
 struct crypto_ablkcipher* skcipher_givcrypt_reqtfm (struct skcipher_givcrypt_request*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int seqiv_givencrypt(struct skcipher_givcrypt_request *req)
{
	struct crypto_ablkcipher *geniv = skcipher_givcrypt_reqtfm(req);
	struct seqiv_ctx *ctx = crypto_ablkcipher_ctx(geniv);
	struct ablkcipher_request *subreq = skcipher_givcrypt_reqctx(req);
	crypto_completion_t complete;
	void *data;
	u8 *info;
	unsigned int ivsize;
	int err;

	ablkcipher_request_set_tfm(subreq, skcipher_geniv_cipher(geniv));

	complete = req->creq.base.complete;
	data = req->creq.base.data;
	info = req->creq.info;

	ivsize = crypto_ablkcipher_ivsize(geniv);

	if (unlikely(!IS_ALIGNED((unsigned long)info,
				 crypto_ablkcipher_alignmask(geniv) + 1))) {
		info = kmalloc(ivsize, req->creq.base.flags &
				       CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL:
								  GFP_ATOMIC);
		if (!info)
			return -ENOMEM;

		complete = seqiv_complete;
		data = req;
	}

	ablkcipher_request_set_callback(subreq, req->creq.base.flags, complete,
					data);
	ablkcipher_request_set_crypt(subreq, req->creq.src, req->creq.dst,
				     req->creq.nbytes, info);

	seqiv_geniv(ctx, info, req->seq, ivsize);
	memcpy(req->giv, info, ivsize);

	err = crypto_ablkcipher_encrypt(subreq);
	if (unlikely(info != req->creq.info))
		seqiv_complete2(req, err);
	return err;
}