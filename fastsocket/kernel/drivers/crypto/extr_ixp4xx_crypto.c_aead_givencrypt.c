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
typedef  int /*<<< orphan*/  u64 ;
struct ixp_ctx {int salted; int /*<<< orphan*/ * salt; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {scalar_t__ cryptlen; int /*<<< orphan*/  assoclen; scalar_t__ iv; } ;
struct aead_givcrypt_request {int /*<<< orphan*/  giv; TYPE_1__ areq; int /*<<< orphan*/  seq; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 struct crypto_aead* aead_givcrypt_reqtfm (struct aead_givcrypt_request*) ; 
 int aead_perform (TYPE_1__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct ixp_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int aead_givencrypt(struct aead_givcrypt_request *req)
{
	struct crypto_aead *tfm = aead_givcrypt_reqtfm(req);
	struct ixp_ctx *ctx = crypto_aead_ctx(tfm);
	unsigned len, ivsize = crypto_aead_ivsize(tfm);
	__be64 seq;

	/* copied from eseqiv.c */
	if (!ctx->salted) {
		get_random_bytes(ctx->salt, ivsize);
		ctx->salted = 1;
	}
	memcpy(req->areq.iv, ctx->salt, ivsize);
	len = ivsize;
	if (ivsize > sizeof(u64)) {
		memset(req->giv, 0, ivsize - sizeof(u64));
		len = sizeof(u64);
	}
	seq = cpu_to_be64(req->seq);
	memcpy(req->giv + ivsize - len, &seq, len);
	return aead_perform(&req->areq, 1, req->areq.assoclen,
			req->areq.cryptlen +ivsize, req->giv);
}