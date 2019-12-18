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
 int tlsv1_client_shutdown (scalar_t__) ; 
 int tlsv1_server_shutdown (scalar_t__) ; 

int tls_connection_shutdown(void *tls_ctx, struct tls_connection *conn)
{
#ifdef CONFIG_TLS_INTERNAL_CLIENT
	if (conn->client)
		return tlsv1_client_shutdown(conn->client);
#endif /* CONFIG_TLS_INTERNAL_CLIENT */
#ifdef CONFIG_TLS_INTERNAL_SERVER
	if (conn->server)
		return tlsv1_server_shutdown(conn->server);
#endif /* CONFIG_TLS_INTERNAL_SERVER */
	return -1;
}