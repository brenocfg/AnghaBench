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
typedef  int /*<<< orphan*/  const u8 ;
struct tlsv1_credentials {int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  crypto_private_key_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/  const*) ; 
 int tlsv1_set_key (struct tlsv1_credentials*,int /*<<< orphan*/  const*,size_t,char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

int tlsv1_set_private_key(struct tlsv1_credentials *cred,
			  const char *private_key,
			  const char *private_key_passwd,
			  const u8 *private_key_blob,
			  size_t private_key_blob_len)
{
	crypto_private_key_free(cred->key);
	cred->key = NULL;

	if (private_key_blob)
		return tlsv1_set_key(cred, private_key_blob,
				     private_key_blob_len,
				     private_key_passwd);

	if (private_key) {
		u8 *buf = NULL;
		size_t len = 0;
		int ret;

		if (buf == NULL) {
			wpa_printf(MSG_INFO, "TLSv1: Failed to read '%s'",
				   private_key);
			return -1;
		}

		ret = tlsv1_set_key(cred, buf, len, private_key_passwd);
		os_free(buf);
		return ret;
	}

	return 0;
}