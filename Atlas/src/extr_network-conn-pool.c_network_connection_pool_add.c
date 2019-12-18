#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network_socket ;
struct TYPE_5__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/ * sock; } ;
typedef  TYPE_1__ network_connection_pool_entry ;
typedef  int /*<<< orphan*/  network_connection_pool ;

/* Variables and functions */
 int /*<<< orphan*/  g_queue_push_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* network_connection_pool_entry_new () ; 
 int /*<<< orphan*/  network_socket_free (int /*<<< orphan*/ *) ; 

network_connection_pool_entry *network_connection_pool_add(network_connection_pool *pool, network_socket *sock) {
	if (pool) {
		network_connection_pool_entry *entry = network_connection_pool_entry_new();
		if (entry) {
			entry->sock = sock;
			entry->pool = pool;
			g_queue_push_tail(pool, entry);

			return entry;
		}
	}

	network_socket_free(sock);
	return NULL;
}