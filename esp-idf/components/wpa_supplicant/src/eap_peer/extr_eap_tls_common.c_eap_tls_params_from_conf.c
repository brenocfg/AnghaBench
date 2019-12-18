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
struct tls_connection_params {int /*<<< orphan*/  private_key_blob_len; int /*<<< orphan*/  private_key_blob; int /*<<< orphan*/  private_key; int /*<<< orphan*/  client_cert_blob_len; int /*<<< orphan*/  client_cert_blob; int /*<<< orphan*/  client_cert; int /*<<< orphan*/  ca_cert_blob_len; int /*<<< orphan*/  ca_cert_blob; int /*<<< orphan*/  ca_cert; int /*<<< orphan*/  flags; } ;
struct eap_ssl_data {scalar_t__ eap_type; } ;
struct eap_sm {scalar_t__ workaround; } ;
struct eap_peer_config {int dummy; } ;

/* Variables and functions */
 scalar_t__ EAP_TYPE_FAST ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  TLS_CONN_DISABLE_SESSION_TICKET ; 
 scalar_t__ eap_tls_check_blob (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_tls_params_from_conf1 (struct tls_connection_params*,struct eap_peer_config*) ; 
 int /*<<< orphan*/  os_memset (struct tls_connection_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_tls_params_from_conf(struct eap_sm *sm,
				    struct eap_ssl_data *data,
				    struct tls_connection_params *params,
				    struct eap_peer_config *config)
{
	os_memset(params, 0, sizeof(*params));
	if (sm->workaround && data->eap_type != EAP_TYPE_FAST) {
		/*
		 * Some deployed authentication servers seem to be unable to
		 * handle the TLS Session Ticket extension (they are supposed
		 * to ignore unrecognized TLS extensions, but end up rejecting
		 * the ClientHello instead). As a workaround, disable use of
		 * TLS Sesson Ticket extension for EAP-TLS, EAP-PEAP, and
		 * EAP-TTLS (EAP-FAST uses session ticket, so any server that
		 * supports EAP-FAST does not need this workaround).
		 */
		params->flags |= TLS_CONN_DISABLE_SESSION_TICKET;
	}

	wpa_printf(MSG_DEBUG, "TLS: using phase1 config options");
	eap_tls_params_from_conf1(params, config);

	/*
	 * Use blob data, if available. Otherwise, leave reference to external
	 * file as-is.
	 */
	if (eap_tls_check_blob(sm, &params->ca_cert, &params->ca_cert_blob,
			       &params->ca_cert_blob_len) ||
	    eap_tls_check_blob(sm, &params->client_cert,
			       &params->client_cert_blob,
			       &params->client_cert_blob_len) ||
	    eap_tls_check_blob(sm, &params->private_key,
			       &params->private_key_blob,
			       &params->private_key_blob_len)) {
		wpa_printf(MSG_INFO, "SSL: Failed to get configuration blobs");
		return -1;
	}

	return 0;
}