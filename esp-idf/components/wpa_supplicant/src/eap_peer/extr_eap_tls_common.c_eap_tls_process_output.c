#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct eap_ssl_data {size_t tls_out_pos; size_t tls_out_limit; int /*<<< orphan*/ * tls_out; int /*<<< orphan*/  conn; TYPE_1__* eap; scalar_t__ include_tls_length; } ;
struct TYPE_2__ {int /*<<< orphan*/  ssl_ctx; } ;
typedef  scalar_t__ EapType ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int EAP_TLS_FLAGS_LENGTH_INCLUDED ; 
 int EAP_TLS_FLAGS_MORE_FRAGMENTS ; 
 scalar_t__ EAP_TYPE_PEAP ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_peer_tls_reset_output (struct eap_ssl_data*) ; 
 struct wpabuf* eap_tls_msg_alloc (scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tls_connection_established (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 scalar_t__ wpabuf_head_u8 (int /*<<< orphan*/ *) ; 
 size_t wpabuf_len (int /*<<< orphan*/ *) ; 
 int* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,scalar_t__,size_t) ; 

__attribute__((used)) static int eap_tls_process_output(struct eap_ssl_data *data, EapType eap_type,
				  int peap_version, u8 id, int ret,
				  struct wpabuf **out_data)
{
	size_t len;
	u8 *flags;
	int more_fragments, length_included;

	if (data->tls_out == NULL)
		return -1;
	len = wpabuf_len(data->tls_out) - data->tls_out_pos;
	wpa_printf(MSG_DEBUG, "SSL: %lu bytes left to be sent out (of total "
		   "%lu bytes)",
		   (unsigned long) len,
		   (unsigned long) wpabuf_len(data->tls_out));

	/*
	 * Limit outgoing message to the configured maximum size. Fragment
	 * message if needed.
	 */
	if (len > data->tls_out_limit) {
		more_fragments = 1;
		len = data->tls_out_limit;
		wpa_printf(MSG_DEBUG, "SSL: sending %lu bytes, more fragments "
			   "will follow", (unsigned long) len);
	} else
		more_fragments = 0;

	length_included = data->tls_out_pos == 0 &&
		(wpabuf_len(data->tls_out) > data->tls_out_limit ||
		 data->include_tls_length);
	if (!length_included &&
	    eap_type == EAP_TYPE_PEAP && peap_version == 0 &&
	    !tls_connection_established(data->eap->ssl_ctx, data->conn)) {
		/*
		 * Windows Server 2008 NPS really wants to have the TLS Message
		 * length included in phase 0 even for unfragmented frames or
		 * it will get very confused with Compound MAC calculation and
		 * Outer TLVs.
		 */
		length_included = 1;
	}

	*out_data = eap_tls_msg_alloc(eap_type, 1 + length_included * 4 + len,
				      EAP_CODE_RESPONSE, id);
	if (*out_data == NULL) {
	    printf("[Debug] out_data is null, return \n");
		return -1;
    } 

	flags = wpabuf_put(*out_data, 1);
	*flags = peap_version;
	if (more_fragments)
		*flags |= EAP_TLS_FLAGS_MORE_FRAGMENTS;
	if (length_included) {
		*flags |= EAP_TLS_FLAGS_LENGTH_INCLUDED;
		wpabuf_put_be32(*out_data, wpabuf_len(data->tls_out));
	}
	wpabuf_put_data(*out_data,
			wpabuf_head_u8(data->tls_out) + data->tls_out_pos,
			len);
	data->tls_out_pos += len;

	if (!more_fragments)
		eap_peer_tls_reset_output(data);

	return ret;
}