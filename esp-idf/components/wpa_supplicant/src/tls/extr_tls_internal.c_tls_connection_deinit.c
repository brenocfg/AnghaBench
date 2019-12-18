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
struct tls_connection {scalar_t__ server; scalar_t__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct tls_connection*) ; 
 int /*<<< orphan*/  tlsv1_client_deinit (scalar_t__) ; 
 int /*<<< orphan*/  tlsv1_server_deinit (scalar_t__) ; 

void tls_connection_deinit(void *tls_ctx, struct tls_connection *conn)
{
	if (conn == NULL)
		return;
#ifdef CONFIG_TLS_INTERNAL_CLIENT
	if (conn->client)
		tlsv1_client_deinit(conn->client);
#endif /* CONFIG_TLS_INTERNAL_CLIENT */
#ifdef CONFIG_TLS_INTERNAL_SERVER
	if (conn->server)
		tlsv1_server_deinit(conn->server);
#endif /* CONFIG_TLS_INTERNAL_SERVER */
	os_free(conn);
}