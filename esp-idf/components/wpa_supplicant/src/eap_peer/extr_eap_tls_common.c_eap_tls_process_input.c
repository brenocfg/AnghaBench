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
struct eap_ssl_data {int /*<<< orphan*/  conn; int /*<<< orphan*/  ssl_ctx; struct wpabuf* tls_out; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 struct wpabuf* eap_peer_tls_data_reassemble (struct eap_ssl_data*,struct wpabuf*,int*) ; 
 int /*<<< orphan*/  eap_peer_tls_reset_input (struct eap_ssl_data*) ; 
 scalar_t__ tls_connection_established (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_connection_get_failed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* tls_connection_handshake (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*,struct wpabuf**) ; 
 int /*<<< orphan*/  wpa_hexdump_buf_key (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_set (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int eap_tls_process_input(struct eap_sm *sm, struct eap_ssl_data *data,
				 const u8 *in_data, size_t in_len,
				 struct wpabuf **out_data)
{
	const struct wpabuf *msg;
	int need_more_input;
	struct wpabuf *appl_data;
	struct wpabuf buf;

	wpabuf_set(&buf, in_data, in_len);
	msg = eap_peer_tls_data_reassemble(data, &buf, &need_more_input);
	if (msg == NULL)
		return need_more_input ? 1 : -1;

	/* Full TLS message reassembled - continue handshake processing */
	if (data->tls_out) {
		/* This should not happen.. */
		wpa_printf(MSG_INFO, "SSL: eap_tls_process_input - pending "
			   "tls_out data even though tls_out_len = 0");
		wpabuf_free(data->tls_out);
		//WPA_ASSERT(data->tls_out == NULL);
	}
	appl_data = NULL;
	data->tls_out = tls_connection_handshake(data->ssl_ctx, data->conn,
						 msg, &appl_data);

	eap_peer_tls_reset_input(data);
	if (appl_data &&
	    tls_connection_established(data->ssl_ctx, data->conn) &&
	    !tls_connection_get_failed(data->ssl_ctx, data->conn)) {
		wpa_hexdump_buf_key(MSG_MSGDUMP, "SSL: Application data",
				    appl_data);
		*out_data = appl_data;
		return 2;
	}

	wpabuf_free(appl_data);

	return 0;
}