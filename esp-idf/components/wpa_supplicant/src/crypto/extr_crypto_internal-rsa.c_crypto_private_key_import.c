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
struct crypto_private_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ crypto_rsa_import_private_key (int /*<<< orphan*/  const*,size_t) ; 
 struct crypto_private_key* pkcs8_enc_key_import (int /*<<< orphan*/  const*,size_t,char const*) ; 
 struct crypto_private_key* pkcs8_key_import (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

struct crypto_private_key *  crypto_private_key_import(const u8 *key,
						      size_t len,
						      const char *passwd)
{
	struct crypto_private_key *res;

	/* First, check for possible PKCS #8 encoding */
	res = pkcs8_key_import(key, len);
	if (res)
		return res;

	if (passwd) {
		/* Try to parse as encrypted PKCS #8 */
		res = pkcs8_enc_key_import(key, len, passwd);
		if (res)
			return res;
	}

	/* Not PKCS#8, so try to import PKCS #1 encoded RSA private key */
	wpa_printf(MSG_DEBUG, "Trying to parse PKCS #1 encoded RSA private "
		   "key");
	return (struct crypto_private_key *)
		crypto_rsa_import_private_key(key, len);
}