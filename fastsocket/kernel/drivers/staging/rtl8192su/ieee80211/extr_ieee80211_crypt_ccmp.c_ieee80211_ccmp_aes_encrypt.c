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

/* Variables and functions */
 int /*<<< orphan*/  crypto_cipher_encrypt_one (void*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void ieee80211_ccmp_aes_encrypt(struct crypto_tfm *tfm,
			     const u8 pt[16], u8 ct[16])
{
	crypto_cipher_encrypt_one((void*)tfm, ct, pt);
}