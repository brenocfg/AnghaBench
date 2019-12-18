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
typedef  int u8 ;
struct crypto_rfc4309_ctx {int /*<<< orphan*/  nonce; struct crypto_aead* child; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  complete; int /*<<< orphan*/  flags; } ;
struct aead_request {int /*<<< orphan*/  assoclen; int /*<<< orphan*/  assoc; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 int* PTR_ALIGN (int*,scalar_t__) ; 
 struct aead_request* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_set_assoc (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,struct crypto_aead*) ; 
 scalar_t__ crypto_aead_alignmask (struct crypto_aead*) ; 
 struct crypto_rfc4309_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_reqsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct aead_request *crypto_rfc4309_crypt(struct aead_request *req)
{
	struct aead_request *subreq = aead_request_ctx(req);
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_rfc4309_ctx *ctx = crypto_aead_ctx(aead);
	struct crypto_aead *child = ctx->child;
	u8 *iv = PTR_ALIGN((u8 *)(subreq + 1) + crypto_aead_reqsize(child),
			   crypto_aead_alignmask(child) + 1);

	/* L' */
	iv[0] = 3;

	memcpy(iv + 1, ctx->nonce, 3);
	memcpy(iv + 4, req->iv, 8);

	aead_request_set_tfm(subreq, child);
	aead_request_set_callback(subreq, req->base.flags, req->base.complete,
				  req->base.data);
	aead_request_set_crypt(subreq, req->src, req->dst, req->cryptlen, iv);
	aead_request_set_assoc(subreq, req->assoc, req->assoclen);

	return subreq;
}