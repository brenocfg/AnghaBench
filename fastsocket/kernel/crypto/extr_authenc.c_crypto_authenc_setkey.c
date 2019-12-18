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
typedef  int /*<<< orphan*/  u8 ;
struct rtattr {scalar_t__ rta_type; int /*<<< orphan*/  rta_len; } ;
struct crypto_authenc_key_param {int /*<<< orphan*/  enckeylen; } ;
struct crypto_authenc_ctx {struct crypto_ablkcipher* enc; struct crypto_ahash* auth; } ;
struct crypto_ahash {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 scalar_t__ CRYPTO_AUTHENC_KEYA_PARAM ; 
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_MASK ; 
 int EINVAL ; 
 scalar_t__ RTA_ALIGN (int /*<<< orphan*/ ) ; 
 struct crypto_authenc_key_param* RTA_DATA (struct rtattr*) ; 
 int /*<<< orphan*/  RTA_OK (struct rtattr*,unsigned int) ; 
 int RTA_PAYLOAD (struct rtattr*) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ablkcipher_clear_flags (struct crypto_ablkcipher*,int) ; 
 int crypto_ablkcipher_get_flags (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int) ; 
 int crypto_ablkcipher_setkey (struct crypto_ablkcipher*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct crypto_authenc_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_get_flags (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int) ; 
 int /*<<< orphan*/  crypto_ahash_clear_flags (struct crypto_ahash*,int) ; 
 int crypto_ahash_get_flags (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_set_flags (struct crypto_ahash*,int) ; 
 int crypto_ahash_setkey (struct crypto_ahash*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int crypto_authenc_setkey(struct crypto_aead *authenc, const u8 *key,
				 unsigned int keylen)
{
	unsigned int authkeylen;
	unsigned int enckeylen;
	struct crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	struct crypto_ahash *auth = ctx->auth;
	struct crypto_ablkcipher *enc = ctx->enc;
	struct rtattr *rta = (void *)key;
	struct crypto_authenc_key_param *param;
	int err = -EINVAL;

	if (!RTA_OK(rta, keylen))
		goto badkey;
	if (rta->rta_type != CRYPTO_AUTHENC_KEYA_PARAM)
		goto badkey;
	if (RTA_PAYLOAD(rta) < sizeof(*param))
		goto badkey;

	param = RTA_DATA(rta);
	enckeylen = be32_to_cpu(param->enckeylen);

	key += RTA_ALIGN(rta->rta_len);
	keylen -= RTA_ALIGN(rta->rta_len);

	if (keylen < enckeylen)
		goto badkey;

	authkeylen = keylen - enckeylen;

	crypto_ahash_clear_flags(auth, CRYPTO_TFM_REQ_MASK);
	crypto_ahash_set_flags(auth, crypto_aead_get_flags(authenc) &
				    CRYPTO_TFM_REQ_MASK);
	err = crypto_ahash_setkey(auth, key, authkeylen);
	crypto_aead_set_flags(authenc, crypto_ahash_get_flags(auth) &
				       CRYPTO_TFM_RES_MASK);

	if (err)
		goto out;

	crypto_ablkcipher_clear_flags(enc, CRYPTO_TFM_REQ_MASK);
	crypto_ablkcipher_set_flags(enc, crypto_aead_get_flags(authenc) &
					 CRYPTO_TFM_REQ_MASK);
	err = crypto_ablkcipher_setkey(enc, key + authkeylen, enckeylen);
	crypto_aead_set_flags(authenc, crypto_ablkcipher_get_flags(enc) &
				       CRYPTO_TFM_RES_MASK);

out:
	return err;

badkey:
	crypto_aead_set_flags(authenc, CRYPTO_TFM_RES_BAD_KEY_LEN);
	goto out;
}