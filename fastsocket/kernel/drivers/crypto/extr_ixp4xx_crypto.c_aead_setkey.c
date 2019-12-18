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
struct ixp_ctx {unsigned int enckey_len; unsigned int authkey_len; int /*<<< orphan*/  authkey; int /*<<< orphan*/  enckey; } ;
struct crypto_authenc_key_param {int /*<<< orphan*/  enckeylen; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 scalar_t__ CRYPTO_AUTHENC_KEYA_PARAM ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 scalar_t__ RTA_ALIGN (int /*<<< orphan*/ ) ; 
 struct crypto_authenc_key_param* RTA_DATA (struct rtattr*) ; 
 int /*<<< orphan*/  RTA_OK (struct rtattr*,unsigned int) ; 
 int RTA_PAYLOAD (struct rtattr*) ; 
 int aead_setup (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_authsize (struct crypto_aead*) ; 
 struct ixp_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int aead_setkey(struct crypto_aead *tfm, const u8 *key,
			unsigned int keylen)
{
	struct ixp_ctx *ctx = crypto_aead_ctx(tfm);
	struct rtattr *rta = (struct rtattr *)key;
	struct crypto_authenc_key_param *param;

	if (!RTA_OK(rta, keylen))
		goto badkey;
	if (rta->rta_type != CRYPTO_AUTHENC_KEYA_PARAM)
		goto badkey;
	if (RTA_PAYLOAD(rta) < sizeof(*param))
		goto badkey;

	param = RTA_DATA(rta);
	ctx->enckey_len = be32_to_cpu(param->enckeylen);

	key += RTA_ALIGN(rta->rta_len);
	keylen -= RTA_ALIGN(rta->rta_len);

	if (keylen < ctx->enckey_len)
		goto badkey;

	ctx->authkey_len = keylen - ctx->enckey_len;
	memcpy(ctx->enckey, key + ctx->authkey_len, ctx->enckey_len);
	memcpy(ctx->authkey, key, ctx->authkey_len);

	return aead_setup(tfm, crypto_aead_authsize(tfm));
badkey:
	ctx->enckey_len = 0;
	crypto_aead_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
	return -EINVAL;
}