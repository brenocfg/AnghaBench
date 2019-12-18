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
typedef  scalar_t__ u8 ;
struct tlsv1_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_ALERT_UNEXPECTED_MESSAGE ; 
 scalar_t__ TLS_CONTENT_TYPE_APPLICATION_DATA ; 
 scalar_t__* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  tls_alert (struct tlsv1_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int tls_process_application_data(struct tlsv1_client *conn, u8 ct,
					const u8 *in_data, size_t *in_len,
					u8 **out_data, size_t *out_len)
{
	const u8 *pos;
	size_t left;

	if (ct != TLS_CONTENT_TYPE_APPLICATION_DATA) {
		wpa_printf(MSG_DEBUG, "TLSv1: Expected Application Data; "
			   "received content type 0x%x", ct);
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	pos = in_data;
	left = *in_len;

	wpa_hexdump(MSG_DEBUG, "TLSv1: Application Data included in Handshake",
		    pos, left);

	*out_data = os_malloc(left);
	if (*out_data) {
		os_memcpy(*out_data, pos, left);
		*out_len = left;
	}

	return 0;
}