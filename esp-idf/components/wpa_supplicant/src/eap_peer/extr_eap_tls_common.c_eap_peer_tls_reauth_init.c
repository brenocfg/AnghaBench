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
struct eap_ssl_data {int /*<<< orphan*/  conn; int /*<<< orphan*/  ssl_ctx; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_peer_tls_reset_input (struct eap_ssl_data*) ; 
 int /*<<< orphan*/  eap_peer_tls_reset_output (struct eap_ssl_data*) ; 
 int tls_connection_shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int eap_peer_tls_reauth_init(struct eap_sm *sm, struct eap_ssl_data *data)
{
	eap_peer_tls_reset_input(data);
	eap_peer_tls_reset_output(data);
	return tls_connection_shutdown(data->ssl_ctx, data->conn);
}