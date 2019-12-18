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
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_MASK ; 
 int ENOSYS ; 
 int /*<<< orphan*/  crypto_ahash_clear_flags (struct crypto_ahash*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int digest_async_nosetkey(struct crypto_ahash *tfm_async, const u8 *key,
			unsigned int keylen)
{
	crypto_ahash_clear_flags(tfm_async, CRYPTO_TFM_RES_MASK);
	return -ENOSYS;
}