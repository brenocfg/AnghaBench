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
struct tls_connection {scalar_t__ server; scalar_t__ client; } ;

/* Variables and functions */
 int tlsv1_client_prf (scalar_t__,char const*,int,int /*<<< orphan*/ *,size_t) ; 
 int tlsv1_server_prf (scalar_t__,char const*,int,int /*<<< orphan*/ *,size_t) ; 

int tls_connection_prf(void *tls_ctx, struct tls_connection *conn,
		       const char *label, int server_random_first,
		       u8 *out, size_t out_len)
{
#ifdef CONFIG_TLS_INTERNAL_CLIENT
	if (conn->client) {
		return tlsv1_client_prf(conn->client, label,
					server_random_first,
					out, out_len);
	}
#endif /* CONFIG_TLS_INTERNAL_CLIENT */
#ifdef CONFIG_TLS_INTERNAL_SERVER
	if (conn->server) {
		return tlsv1_server_prf(conn->server, label,
					server_random_first,
					out, out_len);
	}
#endif /* CONFIG_TLS_INTERNAL_SERVER */
	return -1;
}