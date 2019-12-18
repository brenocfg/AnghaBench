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
typedef  unsigned char u8 ;
struct tlsv1_credentials {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 unsigned char* base64_decode (unsigned char const*,int,size_t*) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 
 int /*<<< orphan*/  os_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pem_dhparams_begin ; 
 int /*<<< orphan*/  pem_dhparams_end ; 
 unsigned char* search_tag (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 scalar_t__ tlsv1_set_dhparams_der (struct tlsv1_credentials*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tlsv1_set_dhparams_blob(struct tlsv1_credentials *cred,
				   const u8 *buf, size_t len)
{
	const u8 *pos, *end;
	unsigned char *der;
	size_t der_len;

	pos = search_tag(pem_dhparams_begin, buf, len);
	if (!pos) {
		wpa_printf(MSG_DEBUG, "TLSv1: No PEM dhparams tag found - "
			   "assume DER format");
		return tlsv1_set_dhparams_der(cred, buf, len);
	}

	wpa_printf(MSG_DEBUG, "TLSv1: Converting PEM format dhparams into DER "
		   "format");

	pos += os_strlen(pem_dhparams_begin);
	end = search_tag(pem_dhparams_end, pos, buf + len - pos);
	if (end == NULL) {
		wpa_printf(MSG_INFO, "TLSv1: Could not find PEM dhparams end "
			   "tag (%s)", pem_dhparams_end);
		return -1;
	}

	der = base64_decode(pos, end - pos, &der_len);
	if (der == NULL) {
		wpa_printf(MSG_INFO, "TLSv1: Could not decode PEM dhparams");
		return -1;
	}

	if (tlsv1_set_dhparams_der(cred, der, der_len) < 0) {
		wpa_printf(MSG_INFO, "TLSv1: Failed to parse PEM dhparams "
			   "DER conversion");
		os_free(der);
		return -1;
	}

	os_free(der);

	return 0;
}