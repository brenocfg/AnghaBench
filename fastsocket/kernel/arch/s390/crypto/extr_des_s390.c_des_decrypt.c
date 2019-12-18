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
struct crypt_s390_des_ctx {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  DES_BLOCK_SIZE ; 
 int /*<<< orphan*/  KM_DEA_DECRYPT ; 
 int /*<<< orphan*/  crypt_s390_km (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct crypt_s390_des_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void des_decrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	struct crypt_s390_des_ctx *dctx = crypto_tfm_ctx(tfm);

	crypt_s390_km(KM_DEA_DECRYPT, dctx->key, out, in, DES_BLOCK_SIZE);
}