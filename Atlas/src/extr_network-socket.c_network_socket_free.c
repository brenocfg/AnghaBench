#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fd; int /*<<< orphan*/  charset_results; int /*<<< orphan*/  charset_connection; int /*<<< orphan*/  charset_client; int /*<<< orphan*/  default_db; int /*<<< orphan*/  event; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; scalar_t__ challenge; scalar_t__ response; int /*<<< orphan*/  recv_queue_raw; int /*<<< orphan*/  recv_queue; int /*<<< orphan*/  send_queue; } ;
typedef  TYPE_1__ network_socket ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_address_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_auth_challenge_free (scalar_t__) ; 
 int /*<<< orphan*/  network_mysqld_auth_response_free (scalar_t__) ; 
 int /*<<< orphan*/  network_queue_free (int /*<<< orphan*/ ) ; 

void network_socket_free(network_socket *s) {
	if (!s) return;

	network_queue_free(s->send_queue);
	network_queue_free(s->recv_queue);
	network_queue_free(s->recv_queue_raw);

	if (s->response) network_mysqld_auth_response_free(s->response);
	if (s->challenge) network_mysqld_auth_challenge_free(s->challenge);

	network_address_free(s->dst);
	network_address_free(s->src);

	event_del(&(s->event));

	if (s->fd != -1) {
		closesocket(s->fd);
	}

	g_string_free(s->default_db, TRUE);
	g_string_free(s->charset_client, TRUE);
	g_string_free(s->charset_connection, TRUE);
	g_string_free(s->charset_results, TRUE);

	g_free(s);
}