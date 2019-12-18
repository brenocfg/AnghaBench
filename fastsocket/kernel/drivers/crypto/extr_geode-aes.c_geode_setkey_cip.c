#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {TYPE_2__* blk; int /*<<< orphan*/  cip; } ;
struct geode_aes_op {unsigned int keylen; TYPE_3__ fallback; int /*<<< orphan*/  key; } ;
struct crypto_tfm {int crt_flags; } ;
struct TYPE_4__ {int crt_flags; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 unsigned int AES_KEYSIZE_128 ; 
 unsigned int AES_KEYSIZE_192 ; 
 unsigned int AES_KEYSIZE_256 ; 
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_MASK ; 
 int EINVAL ; 
 unsigned int crypto_cipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 struct geode_aes_op* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int geode_setkey_cip(struct crypto_tfm *tfm, const u8 *key,
		unsigned int len)
{
	struct geode_aes_op *op = crypto_tfm_ctx(tfm);
	unsigned int ret;

	op->keylen = len;

	if (len == AES_KEYSIZE_128) {
		memcpy(op->key, key, len);
		return 0;
	}

	if (len != AES_KEYSIZE_192 && len != AES_KEYSIZE_256) {
		/* not supported at all */
		tfm->crt_flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
		return -EINVAL;
	}

	/*
	 * The requested key size is not supported by HW, do a fallback
	 */
	op->fallback.blk->base.crt_flags &= ~CRYPTO_TFM_REQ_MASK;
	op->fallback.blk->base.crt_flags |= (tfm->crt_flags & CRYPTO_TFM_REQ_MASK);

	ret = crypto_cipher_setkey(op->fallback.cip, key, len);
	if (ret) {
		tfm->crt_flags &= ~CRYPTO_TFM_RES_MASK;
		tfm->crt_flags |= (op->fallback.blk->base.crt_flags & CRYPTO_TFM_RES_MASK);
	}
	return ret;
}