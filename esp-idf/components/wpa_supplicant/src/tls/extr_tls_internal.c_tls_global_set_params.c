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
struct tlsv1_credentials {int dummy; } ;
struct tls_global {int server; struct tlsv1_credentials* server_cred; } ;
struct tls_connection_params {int /*<<< orphan*/  dh_blob_len; int /*<<< orphan*/  dh_blob; int /*<<< orphan*/  dh_file; int /*<<< orphan*/  private_key_blob_len; int /*<<< orphan*/  private_key_blob; int /*<<< orphan*/  private_key_passwd; int /*<<< orphan*/  private_key; int /*<<< orphan*/  client_cert_blob_len; int /*<<< orphan*/  client_cert_blob; int /*<<< orphan*/  client_cert; int /*<<< orphan*/  ca_path; int /*<<< orphan*/  ca_cert_blob_len; int /*<<< orphan*/  ca_cert_blob; int /*<<< orphan*/  ca_cert; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 struct tlsv1_credentials* tlsv1_cred_alloc () ; 
 int /*<<< orphan*/  tlsv1_cred_free (struct tlsv1_credentials*) ; 
 scalar_t__ tlsv1_set_ca_cert (struct tlsv1_credentials*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tlsv1_set_cert (struct tlsv1_credentials*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tlsv1_set_dhparams (struct tlsv1_credentials*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tlsv1_set_private_key (struct tlsv1_credentials*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int tls_global_set_params(void *tls_ctx,
			  const struct tls_connection_params *params)
{
#ifdef CONFIG_TLS_INTERNAL_SERVER
	struct tls_global *global = tls_ctx;
	struct tlsv1_credentials *cred;

	/* Currently, global parameters are only set when running in server
	 * mode. */
	global->server = 1;
	tlsv1_cred_free(global->server_cred);
	global->server_cred = cred = tlsv1_cred_alloc();
	if (cred == NULL)
		return -1;

	if (tlsv1_set_ca_cert(cred, params->ca_cert, params->ca_cert_blob,
			      params->ca_cert_blob_len, params->ca_path)) {
		wpa_printf(MSG_INFO, "TLS: Failed to configure trusted CA "
			   "certificates");
		return -1;
	}

	if (tlsv1_set_cert(cred, params->client_cert, params->client_cert_blob,
			   params->client_cert_blob_len)) {
		wpa_printf(MSG_INFO, "TLS: Failed to configure server "
			   "certificate");
		return -1;
	}

	if (tlsv1_set_private_key(cred, params->private_key,
				  params->private_key_passwd,
				  params->private_key_blob,
				  params->private_key_blob_len)) {
		wpa_printf(MSG_INFO, "TLS: Failed to load private key");
		return -1;
	}

	if (tlsv1_set_dhparams(cred, params->dh_file, params->dh_blob,
			       params->dh_blob_len)) {
		wpa_printf(MSG_INFO, "TLS: Failed to load DH parameters");
		return -1;
	}

	return 0;
#else /* CONFIG_TLS_INTERNAL_SERVER */
	return -1;
#endif /* CONFIG_TLS_INTERNAL_SERVER */
}