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
typedef  int /*<<< orphan*/  tls_session_ticket_cb ;
struct tls_connection {scalar_t__ server; scalar_t__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  tlsv1_client_set_session_ticket_cb (scalar_t__,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tlsv1_server_set_session_ticket_cb (scalar_t__,int /*<<< orphan*/ ,void*) ; 

int tls_connection_set_session_ticket_cb(void *tls_ctx,
					 struct tls_connection *conn,
					 tls_session_ticket_cb cb,
					 void *ctx)
{
#ifdef CONFIG_TLS_INTERNAL_CLIENT
	if (conn->client) {
		tlsv1_client_set_session_ticket_cb(conn->client, cb, ctx);
		return 0;
	}
#endif /* CONFIG_TLS_INTERNAL_CLIENT */
#ifdef CONFIG_TLS_INTERNAL_SERVER
	if (conn->server) {
		tlsv1_server_set_session_ticket_cb(conn->server, cb, ctx);
		return 0;
	}
#endif /* CONFIG_TLS_INTERNAL_SERVER */
	return -1;
}