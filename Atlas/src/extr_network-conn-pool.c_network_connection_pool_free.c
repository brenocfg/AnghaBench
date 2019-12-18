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
typedef  int /*<<< orphan*/  network_connection_pool_entry ;
typedef  int /*<<< orphan*/  network_connection_pool ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_queue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_queue_pop_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_connection_pool_entry_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void network_connection_pool_free(network_connection_pool *pool) {
	if (pool) {
		network_connection_pool_entry *entry = NULL;
		while ((entry = g_queue_pop_head(pool))) network_connection_pool_entry_free(entry, TRUE);
		g_queue_free(pool);
	}
}