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
 unsigned char* base64_decode (int /*<<< orphan*/  const*,int,size_t*) ; 
 struct crypto_private_key* crypto_private_key_import (unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 
 int /*<<< orphan*/  os_strlen (char*) ; 
 char* pem_key2_begin ; 
 char* pem_key2_end ; 
 char* pem_key_begin ; 
 char* pem_key_end ; 
 int /*<<< orphan*/ * search_tag (char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct crypto_private_key * tlsv1_set_key_pem(const u8 *key, size_t len)
{
	const u8 *pos, *end;
	unsigned char *der;
	size_t der_len;
	struct crypto_private_key *pkey;

	pos = search_tag(pem_key_begin, key, len);
	if (!pos) {
		pos = search_tag(pem_key2_begin, key, len);
		if (!pos)
			return NULL;
		pos += os_strlen(pem_key2_begin);
		end = search_tag(pem_key2_end, pos, key + len - pos);
		if (!end)
			return NULL;
	} else {
		const u8 *pos2;
		pos += os_strlen(pem_key_begin);
		end = search_tag(pem_key_end, pos, key + len - pos);
		if (!end)
			return NULL;
		pos2 = search_tag("Proc-Type: 4,ENCRYPTED", pos, end - pos);
		if (pos2) {
			wpa_printf(MSG_DEBUG, "TLSv1: Unsupported private key "
				   "format (Proc-Type/DEK-Info)");
			return NULL;
		}
	}

	der = base64_decode(pos, end - pos, &der_len);
	if (!der)
		return NULL;
	pkey = crypto_private_key_import(der, der_len, NULL);
	os_free(der);
	return pkey;
}