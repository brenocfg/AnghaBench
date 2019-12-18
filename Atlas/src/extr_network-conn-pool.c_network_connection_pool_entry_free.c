#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ network_socket ;
struct TYPE_7__ {TYPE_1__* sock; } ;
typedef  TYPE_2__ network_connection_pool_entry ;
typedef  scalar_t__ gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (TYPE_2__*) ; 
 int /*<<< orphan*/  network_socket_free (TYPE_1__*) ; 

void network_connection_pool_entry_free(network_connection_pool_entry *e, gboolean free_sock) {
	if (!e) return;

	if (e->sock && free_sock) {
		network_socket *sock = e->sock;
			
		event_del(&(sock->event));
		network_socket_free(sock);
	}

	g_free(e);
}