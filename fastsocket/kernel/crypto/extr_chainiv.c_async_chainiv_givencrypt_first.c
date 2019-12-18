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
struct skcipher_givcrypt_request {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct async_chainiv_ctx {int /*<<< orphan*/  state; int /*<<< orphan*/  iv; } ;
struct TYPE_2__ {scalar_t__ givencrypt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAINIV_STATE_INUSE ; 
 int async_chainiv_givencrypt (struct skcipher_givcrypt_request*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* crypto_ablkcipher_crt (struct crypto_ablkcipher*) ; 
 struct async_chainiv_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_default_rng ; 
 int crypto_rng_get_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_ablkcipher* skcipher_givcrypt_reqtfm (struct skcipher_givcrypt_request*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int async_chainiv_givencrypt_first(struct skcipher_givcrypt_request *req)
{
	struct crypto_ablkcipher *geniv = skcipher_givcrypt_reqtfm(req);
	struct async_chainiv_ctx *ctx = crypto_ablkcipher_ctx(geniv);
	int err = 0;

	if (test_and_set_bit(CHAINIV_STATE_INUSE, &ctx->state))
		goto out;

	if (crypto_ablkcipher_crt(geniv)->givencrypt !=
	    async_chainiv_givencrypt_first)
		goto unlock;

	crypto_ablkcipher_crt(geniv)->givencrypt = async_chainiv_givencrypt;
	err = crypto_rng_get_bytes(crypto_default_rng, ctx->iv,
				   crypto_ablkcipher_ivsize(geniv));

unlock:
	clear_bit(CHAINIV_STATE_INUSE, &ctx->state);

	if (err)
		return err;

out:
	return async_chainiv_givencrypt(req);
}