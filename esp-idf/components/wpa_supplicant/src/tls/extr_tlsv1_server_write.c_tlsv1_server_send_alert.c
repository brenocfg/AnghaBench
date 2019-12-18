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
typedef  void* u8 ;
struct TYPE_2__ {int tls_version; } ;
struct tlsv1_server {TYPE_1__ rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_CONTENT_TYPE_ALERT ; 
 int TLS_VERSION ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (void**,int) ; 
 void** os_malloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,void*,void*) ; 

u8 * tlsv1_server_send_alert(struct tlsv1_server *conn, u8 level,
			     u8 description, size_t *out_len)
{
	u8 *alert, *pos, *length;

	wpa_printf(MSG_DEBUG, "TLSv1: Send Alert(%d:%d)", level, description);
	*out_len = 0;

	alert = os_malloc(10);
	if (alert == NULL)
		return NULL;

	pos = alert;

	/* TLSPlaintext */
	/* ContentType type */
	*pos++ = TLS_CONTENT_TYPE_ALERT;
	/* ProtocolVersion version */
	WPA_PUT_BE16(pos, conn->rl.tls_version ? conn->rl.tls_version :
		     TLS_VERSION);
	pos += 2;
	/* uint16 length (to be filled) */
	length = pos;
	pos += 2;
	/* opaque fragment[TLSPlaintext.length] */

	/* Alert */
	/* AlertLevel level */
	*pos++ = level;
	/* AlertDescription description */
	*pos++ = description;

	WPA_PUT_BE16(length, pos - length - 2);
	*out_len = pos - alert;

	return alert;
}