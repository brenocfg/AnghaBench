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
struct crypto_authenc_ctx {int /*<<< orphan*/  enc; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  complete; } ;
struct aead_request {unsigned int cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; int /*<<< orphan*/ * iv; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ablkcipher_request_set_callback (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ablkcipher_request_set_crypt (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ablkcipher_request_set_tfm (struct ablkcipher_request*,int /*<<< orphan*/ ) ; 
 struct ablkcipher_request* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 int crypto_ablkcipher_decrypt (struct ablkcipher_request*) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_authenc_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_authenc_iverify (struct aead_request*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int crypto_authenc_decrypt(struct aead_request *req)
{
	struct crypto_aead *authenc = crypto_aead_reqtfm(req);
	struct crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	struct ablkcipher_request *abreq = aead_request_ctx(req);
	unsigned int cryptlen = req->cryptlen;
	unsigned int authsize = crypto_aead_authsize(authenc);
	u8 *iv = req->iv;
	int err;

	if (cryptlen < authsize)
		return -EINVAL;
	cryptlen -= authsize;

	err = crypto_authenc_iverify(req, iv, cryptlen);
	if (err)
		return err;

	ablkcipher_request_set_tfm(abreq, ctx->enc);
	ablkcipher_request_set_callback(abreq, aead_request_flags(req),
					req->base.complete, req->base.data);
	ablkcipher_request_set_crypt(abreq, req->src, req->dst, cryptlen, iv);

	return crypto_ablkcipher_decrypt(abreq);
}