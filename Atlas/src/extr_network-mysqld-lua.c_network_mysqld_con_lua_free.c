#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  queries; } ;
struct TYPE_6__ {TYPE_1__ injected; } ;
typedef  TYPE_2__ network_mysqld_con_lua_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_2__*) ; 
 int /*<<< orphan*/  network_injection_queue_free (int /*<<< orphan*/ ) ; 

void network_mysqld_con_lua_free(network_mysqld_con_lua_t *st) {
	if (!st) return;

	network_injection_queue_free(st->injected.queries);

	g_free(st);
}