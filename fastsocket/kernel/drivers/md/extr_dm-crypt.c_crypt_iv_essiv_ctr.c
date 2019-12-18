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
struct dm_target {char* error; } ;
struct crypto_hash {int dummy; } ;
typedef  struct crypto_hash crypto_cipher ;
struct TYPE_3__ {struct crypto_hash* hash_tfm; struct crypto_hash* tfm; int /*<<< orphan*/ * salt; } ;
struct TYPE_4__ {TYPE_1__ essiv; } ;
struct crypt_config {TYPE_2__ iv_gen_private; int /*<<< orphan*/  tfm; int /*<<< orphan*/  cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_hash*) ; 
 int PTR_ERR (struct crypto_hash*) ; 
 scalar_t__ crypto_ablkcipher_ivsize (int /*<<< orphan*/ ) ; 
 struct crypto_hash* crypto_alloc_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_hash* crypto_alloc_hash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_cipher_blocksize (struct crypto_hash*) ; 
 int /*<<< orphan*/  crypto_free_cipher (struct crypto_hash*) ; 
 int /*<<< orphan*/  crypto_free_hash (struct crypto_hash*) ; 
 int /*<<< orphan*/  crypto_hash_digestsize (struct crypto_hash*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypt_iv_essiv_ctr(struct crypt_config *cc, struct dm_target *ti,
			      const char *opts)
{
	struct crypto_cipher *essiv_tfm = NULL;
	struct crypto_hash *hash_tfm = NULL;
	u8 *salt = NULL;
	int err;

	if (!opts) {
		ti->error = "Digest algorithm missing for ESSIV mode";
		return -EINVAL;
	}

	/* Allocate hash algorithm */
	hash_tfm = crypto_alloc_hash(opts, 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(hash_tfm)) {
		ti->error = "Error initializing ESSIV hash";
		err = PTR_ERR(hash_tfm);
		goto bad;
	}

	salt = kzalloc(crypto_hash_digestsize(hash_tfm), GFP_KERNEL);
	if (!salt) {
		ti->error = "Error kmallocing salt storage in ESSIV";
		err = -ENOMEM;
		goto bad;
	}

	/* Allocate essiv_tfm */
	essiv_tfm = crypto_alloc_cipher(cc->cipher, 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(essiv_tfm)) {
		ti->error = "Error allocating crypto tfm for ESSIV";
		err = PTR_ERR(essiv_tfm);
		goto bad;
	}
	if (crypto_cipher_blocksize(essiv_tfm) !=
	    crypto_ablkcipher_ivsize(cc->tfm)) {
		ti->error = "Block size of ESSIV cipher does "
			    "not match IV size of block cipher";
		err = -EINVAL;
		goto bad;
	}

	cc->iv_gen_private.essiv.salt = salt;
	cc->iv_gen_private.essiv.tfm = essiv_tfm;
	cc->iv_gen_private.essiv.hash_tfm = hash_tfm;

	return 0;

bad:
	if (essiv_tfm && !IS_ERR(essiv_tfm))
		crypto_free_cipher(essiv_tfm);
	if (hash_tfm && !IS_ERR(hash_tfm))
		crypto_free_hash(hash_tfm);
	kfree(salt);
	return err;
}