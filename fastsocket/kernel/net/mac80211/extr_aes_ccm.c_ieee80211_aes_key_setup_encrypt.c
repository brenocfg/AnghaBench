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
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALG_CCMP_KEY_LEN ; 
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int /*<<< orphan*/  IS_ERR (struct crypto_cipher*) ; 
 struct crypto_cipher* crypto_alloc_cipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_cipher_setkey (struct crypto_cipher*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

struct crypto_cipher *ieee80211_aes_key_setup_encrypt(const u8 key[])
{
	struct crypto_cipher *tfm;

	tfm = crypto_alloc_cipher("aes", 0, CRYPTO_ALG_ASYNC);
	if (!IS_ERR(tfm))
		crypto_cipher_setkey(tfm, key, ALG_CCMP_KEY_LEN);

	return tfm;
}