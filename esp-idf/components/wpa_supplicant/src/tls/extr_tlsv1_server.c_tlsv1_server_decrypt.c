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
struct tlsv1_server {int /*<<< orphan*/  rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ TLS_ALERT_DECODE_ERROR ; 
 scalar_t__ TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 scalar_t__ TLS_ALERT_LEVEL_WARNING ; 
 scalar_t__ TLS_ALERT_UNEXPECTED_MESSAGE ; 
 scalar_t__ TLS_CONTENT_TYPE_ALERT ; 
 scalar_t__ TLS_CONTENT_TYPE_APPLICATION_DATA ; 
 int tlsv1_record_receive (int /*<<< orphan*/ *,scalar_t__ const*,int,scalar_t__*,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int tlsv1_server_decrypt(struct tlsv1_server *conn,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t out_len)
{
	const u8 *in_end, *pos;
	int used;
	u8 alert, *out_end, *out_pos, ct;
	size_t olen;

	pos = in_data;
	in_end = in_data + in_len;
	out_pos = out_data;
	out_end = out_data + out_len;

	while (pos < in_end) {
		ct = pos[0];
		olen = out_end - out_pos;
		used = tlsv1_record_receive(&conn->rl, pos, in_end - pos,
					    out_pos, &olen, &alert);
		if (used < 0) {
			wpa_printf(MSG_DEBUG, "TLSv1: Record layer processing "
				   "failed");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL, alert);
			return -1;
		}
		if (used == 0) {
			/* need more data */
			wpa_printf(MSG_DEBUG, "TLSv1: Partial processing not "
				   "yet supported");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL, alert);
			return -1;
		}

		if (ct == TLS_CONTENT_TYPE_ALERT) {
			if (olen < 2) {
				wpa_printf(MSG_DEBUG, "TLSv1: Alert "
					   "underflow");
				tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
						   TLS_ALERT_DECODE_ERROR);
				return -1;
			}
			wpa_printf(MSG_DEBUG, "TLSv1: Received alert %d:%d",
				   out_pos[0], out_pos[1]);
			if (out_pos[0] == TLS_ALERT_LEVEL_WARNING) {
				/* Continue processing */
				pos += used;
				continue;
			}

			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   out_pos[1]);
			return -1;
		}

		if (ct != TLS_CONTENT_TYPE_APPLICATION_DATA) {
			wpa_printf(MSG_DEBUG, "TLSv1: Unexpected content type "
				   "0x%x", pos[0]);
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_UNEXPECTED_MESSAGE);
			return -1;
		}

		out_pos += olen;
		if (out_pos > out_end) {
			wpa_printf(MSG_DEBUG, "TLSv1: Buffer not large enough "
				   "for processing the received record");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_INTERNAL_ERROR);
			return -1;
		}

		pos += used;
	}

	return out_pos - out_data;
}