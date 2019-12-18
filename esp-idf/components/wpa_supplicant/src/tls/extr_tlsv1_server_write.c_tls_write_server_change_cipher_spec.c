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
struct tlsv1_server {int /*<<< orphan*/  rl; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_CHANGE_CIPHER_SPEC ; 
 int /*<<< orphan*/  TLS_CONTENT_TYPE_CHANGE_CIPHER_SPEC ; 
 scalar_t__ tlsv1_record_change_write_cipher (int /*<<< orphan*/ *) ; 
 scalar_t__ tlsv1_record_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tls_write_server_change_cipher_spec(struct tlsv1_server *conn,
					       u8 **msgpos, u8 *end)
{
	size_t rlen;
	u8 payload[1];

	wpa_printf(MSG_DEBUG, "TLSv1: Send ChangeCipherSpec");

	payload[0] = TLS_CHANGE_CIPHER_SPEC;

	if (tlsv1_record_send(&conn->rl, TLS_CONTENT_TYPE_CHANGE_CIPHER_SPEC,
			      *msgpos, end - *msgpos, payload, sizeof(payload),
			      &rlen) < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to create a record");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	if (tlsv1_record_change_write_cipher(&conn->rl) < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to set write cipher for "
			   "record layer");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	*msgpos += rlen;

	return 0;
}