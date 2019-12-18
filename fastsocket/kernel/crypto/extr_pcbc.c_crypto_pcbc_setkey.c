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
struct crypto_tfm {int dummy; } ;
struct crypto_pcbc_ctx {struct crypto_cipher* child; } ;
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_MASK ; 
 int /*<<< orphan*/  crypto_cipher_clear_flags (struct crypto_cipher*,int) ; 
 int crypto_cipher_get_flags (struct crypto_cipher*) ; 
 int /*<<< orphan*/  crypto_cipher_set_flags (struct crypto_cipher*,int) ; 
 int crypto_cipher_setkey (struct crypto_cipher*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct crypto_pcbc_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int crypto_tfm_get_flags (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_tfm_set_flags (struct crypto_tfm*,int) ; 

__attribute__((used)) static int crypto_pcbc_setkey(struct crypto_tfm *parent, const u8 *key,
			      unsigned int keylen)
{
	struct crypto_pcbc_ctx *ctx = crypto_tfm_ctx(parent);
	struct crypto_cipher *child = ctx->child;
	int err;

	crypto_cipher_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(child, crypto_tfm_get_flags(parent) &
				CRYPTO_TFM_REQ_MASK);
	err = crypto_cipher_setkey(child, key, keylen);
	crypto_tfm_set_flags(parent, crypto_cipher_get_flags(child) &
			     CRYPTO_TFM_RES_MASK);
	return err;
}