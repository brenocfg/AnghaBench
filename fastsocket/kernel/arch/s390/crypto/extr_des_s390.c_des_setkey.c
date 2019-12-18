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
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;
struct crypt_s390_des_ctx {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int crypto_des_check_key (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 struct crypt_s390_des_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int des_setkey(struct crypto_tfm *tfm, const u8 *key,
		      unsigned int keylen)
{
	struct crypt_s390_des_ctx *dctx = crypto_tfm_ctx(tfm);
	u32 *flags = &tfm->crt_flags;
	int ret;

	/* test if key is valid (not a weak key) */
	ret = crypto_des_check_key(key, keylen, flags);
	if (ret == 0)
		memcpy(dctx->key, key, keylen);
	return ret;
}