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
struct seqiv_ctx {int /*<<< orphan*/  lock; int /*<<< orphan*/  salt; } ;
struct crypto_aead {int dummy; } ;
struct aead_givcrypt_request {int dummy; } ;
struct TYPE_2__ {scalar_t__ givencrypt; } ;

/* Variables and functions */
 struct crypto_aead* aead_givcrypt_reqtfm (struct aead_givcrypt_request*) ; 
 TYPE_1__* crypto_aead_crt (struct crypto_aead*) ; 
 struct seqiv_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_ivsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_default_rng ; 
 int crypto_rng_get_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int seqiv_aead_givencrypt (struct aead_givcrypt_request*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int seqiv_aead_givencrypt_first(struct aead_givcrypt_request *req)
{
	struct crypto_aead *geniv = aead_givcrypt_reqtfm(req);
	struct seqiv_ctx *ctx = crypto_aead_ctx(geniv);
	int err = 0;

	spin_lock_bh(&ctx->lock);
	if (crypto_aead_crt(geniv)->givencrypt != seqiv_aead_givencrypt_first)
		goto unlock;

	crypto_aead_crt(geniv)->givencrypt = seqiv_aead_givencrypt;
	err = crypto_rng_get_bytes(crypto_default_rng, ctx->salt,
				   crypto_aead_ivsize(geniv));

unlock:
	spin_unlock_bh(&ctx->lock);

	if (err)
		return err;

	return seqiv_aead_givencrypt(req);
}