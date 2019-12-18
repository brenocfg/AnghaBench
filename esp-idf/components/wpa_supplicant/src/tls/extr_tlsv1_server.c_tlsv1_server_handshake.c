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
struct tlsv1_server {scalar_t__ state; int /*<<< orphan*/  alert_description; scalar_t__ alert_level; int /*<<< orphan*/  rl; } ;

/* Variables and functions */
 scalar_t__ FAILED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int tlsv1_record_receive (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tlsv1_server_handshake_write (struct tlsv1_server*,size_t*) ; 
 scalar_t__ tlsv1_server_process_handshake (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * tlsv1_server_send_alert (struct tlsv1_server*,scalar_t__,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

u8 * tlsv1_server_handshake(struct tlsv1_server *conn,
			    const u8 *in_data, size_t in_len,
			    size_t *out_len)
{
	const u8 *pos, *end;
	u8 *msg = NULL, *in_msg, *in_pos, *in_end, alert, ct;
	size_t in_msg_len;
	int used;

	if (in_data == NULL || in_len == 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: No input data to server");
		return NULL;
	}

	pos = in_data;
	end = in_data + in_len;
	in_msg = os_malloc(in_len);
	if (in_msg == NULL)
		return NULL;

	/* Each received packet may include multiple records */
	while (pos < end) {
		in_msg_len = in_len;
		used = tlsv1_record_receive(&conn->rl, pos, end - pos,
					    in_msg, &in_msg_len, &alert);
		if (used < 0) {
			wpa_printf(MSG_DEBUG, "TLSv1: Processing received "
				   "record failed");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL, alert);
			goto failed;
		}
		if (used == 0) {
			/* need more data */
			wpa_printf(MSG_DEBUG, "TLSv1: Partial processing not "
				   "yet supported");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL, alert);
			goto failed;
		}
		ct = pos[0];

		in_pos = in_msg;
		in_end = in_msg + in_msg_len;

		/* Each received record may include multiple messages of the
		 * same ContentType. */
		while (in_pos < in_end) {
			in_msg_len = in_end - in_pos;
			if (tlsv1_server_process_handshake(conn, ct, in_pos,
							   &in_msg_len) < 0)
				goto failed;
			in_pos += in_msg_len;
		}

		pos += used;
	}

	os_free(in_msg);
	in_msg = NULL;

	msg = tlsv1_server_handshake_write(conn, out_len);

failed:
	os_free(in_msg);
	if (conn->alert_level) {
		if (conn->state == FAILED) {
			/* Avoid alert loops */
			wpa_printf(MSG_DEBUG, "TLSv1: Drop alert loop");
			os_free(msg);
			return NULL;
		}
		conn->state = FAILED;
		os_free(msg);
		msg = tlsv1_server_send_alert(conn, conn->alert_level,
					      conn->alert_description,
					      out_len);
	}

	return msg;
}