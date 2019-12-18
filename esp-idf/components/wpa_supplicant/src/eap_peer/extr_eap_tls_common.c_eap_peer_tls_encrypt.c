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
struct wpabuf {int dummy; } ;
struct eap_ssl_data {int /*<<< orphan*/ * tls_out; int /*<<< orphan*/  conn; int /*<<< orphan*/  ssl_ctx; } ;
struct eap_sm {int dummy; } ;
typedef  int /*<<< orphan*/  EapType ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  eap_peer_tls_reset_output (struct eap_ssl_data*) ; 
 int eap_tls_process_output (struct eap_ssl_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf**) ; 
 int /*<<< orphan*/ * tls_connection_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 
 scalar_t__ wpabuf_len (struct wpabuf const*) ; 

int eap_peer_tls_encrypt(struct eap_sm *sm, struct eap_ssl_data *data,
			 EapType eap_type, int peap_version, u8 id,
			 const struct wpabuf *in_data,
			 struct wpabuf **out_data)
{
	if (in_data) {
		eap_peer_tls_reset_output(data);
		data->tls_out = tls_connection_encrypt(data->ssl_ctx,
						       data->conn, in_data);
		if (data->tls_out == NULL) {
			wpa_printf(MSG_INFO, "SSL: Failed to encrypt Phase 2 "
				   "data (in_len=%lu)",
				   (unsigned long) wpabuf_len(in_data));
			eap_peer_tls_reset_output(data);
			return -1;
		}
	}

	return eap_tls_process_output(data, eap_type, peap_version, id, 0,
				      out_data);
}