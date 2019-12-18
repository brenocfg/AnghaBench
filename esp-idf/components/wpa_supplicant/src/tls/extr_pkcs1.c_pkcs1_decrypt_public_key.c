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
typedef  int u8 ;
struct crypto_rsa_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ crypto_rsa_exptmod (int const*,size_t,int*,size_t*,struct crypto_rsa_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memmove (int*,int*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int pkcs1_decrypt_public_key(struct crypto_rsa_key *key,
			     const u8 *crypt, size_t crypt_len,
			     u8 *plain, size_t *plain_len)
{
	size_t len;
	u8 *pos;

	len = *plain_len;
	if (crypto_rsa_exptmod(crypt, crypt_len, plain, &len, key, 0) < 0)
		return -1;

	/*
	 * PKCS #1 v1.5, 8.1:
	 *
	 * EB = 00 || BT || PS || 00 || D
	 * BT = 00 or 01
	 * PS = k-3-||D|| times (00 if BT=00) or (FF if BT=01)
	 * k = length of modulus in octets
	 */

	if (len < 3 + 8 + 16 /* min hash len */ ||
	    plain[0] != 0x00 || (plain[1] != 0x00 && plain[1] != 0x01)) {
		wpa_printf(MSG_INFO, "LibTomCrypt: Invalid signature EB "
			   "structure");
		return -1;
	}

	pos = plain + 3;
	if (plain[1] == 0x00) {
		/* BT = 00 */
		if (plain[2] != 0x00) {
			wpa_printf(MSG_INFO, "LibTomCrypt: Invalid signature "
				   "PS (BT=00)");
			return -1;
		}
		while (pos + 1 < plain + len && *pos == 0x00 && pos[1] == 0x00)
			pos++;
	} else {
		/* BT = 01 */
		if (plain[2] != 0xff) {
			wpa_printf(MSG_INFO, "LibTomCrypt: Invalid signature "
				   "PS (BT=01)");
			return -1;
		}
		while (pos < plain + len && *pos == 0xff)
			pos++;
	}

	if (pos - plain - 2 < 8) {
		/* PKCS #1 v1.5, 8.1: At least eight octets long PS */
		wpa_printf(MSG_INFO, "LibTomCrypt: Too short signature "
			   "padding");
		return -1;
	}

	if (pos + 16 /* min hash len */ >= plain + len || *pos != 0x00) {
		wpa_printf(MSG_INFO, "LibTomCrypt: Invalid signature EB "
			   "structure (2)");
		return -1;
	}
	pos++;
	len -= pos - plain;

	/* Strip PKCS #1 header */
	os_memmove(plain, pos, len);
	*plain_len = len;

	return 0;
}