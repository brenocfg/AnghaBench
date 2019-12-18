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
struct crypto_rsa_key {int dummy; } ;
struct crypto_private_key {int dummy; } ;

/* Variables and functions */
 int pkcs1_v15_private_key_decrypt (struct crypto_rsa_key*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t*) ; 

int  crypto_private_key_decrypt_pkcs1_v15(struct crypto_private_key *key,
					 const u8 *in, size_t inlen,
					 u8 *out, size_t *outlen)
{
	return pkcs1_v15_private_key_decrypt((struct crypto_rsa_key *) key,
					     in, inlen, out, outlen);
}