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
typedef  int /*<<< orphan*/  u32 ;
struct hifn_device {int /*<<< orphan*/  flags; } ;
struct hifn_context {unsigned int keysize; int /*<<< orphan*/  key; struct hifn_device* dev; } ;
struct crypto_tfm {int crt_flags; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_WEAK_KEY ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_WEAK_KEY ; 
 int DES_EXPKEY_WORDS ; 
 int EINVAL ; 
 unsigned int HIFN_DES_KEY_LENGTH ; 
 int /*<<< orphan*/  HIFN_FLAG_OLD_KEY ; 
 unsigned int HIFN_MAX_CRYPT_KEY_LENGTH ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 struct hifn_context* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int des_ekey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hifn_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
		unsigned int len)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct hifn_context *ctx = crypto_tfm_ctx(tfm);
	struct hifn_device *dev = ctx->dev;

	if (len > HIFN_MAX_CRYPT_KEY_LENGTH) {
		crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -1;
	}

	if (len == HIFN_DES_KEY_LENGTH) {
		u32 tmp[DES_EXPKEY_WORDS];
		int ret = des_ekey(tmp, key);
		
		if (unlikely(ret == 0) && (tfm->crt_flags & CRYPTO_TFM_REQ_WEAK_KEY)) {
			tfm->crt_flags |= CRYPTO_TFM_RES_WEAK_KEY;
			return -EINVAL;
		}
	}

	dev->flags &= ~HIFN_FLAG_OLD_KEY;

	memcpy(ctx->key, key, len);
	ctx->keysize = len;

	return 0;
}