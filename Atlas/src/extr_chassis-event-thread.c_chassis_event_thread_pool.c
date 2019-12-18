#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network_connection_pool ;
struct TYPE_3__ {int /*<<< orphan*/  pools; } ;
typedef  TYPE_1__ network_backend_t ;
typedef  int /*<<< orphan*/  guint ;

/* Variables and functions */
 int /*<<< orphan*/  GPOINTER_TO_UINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_private_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_ptr_array_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_index ; 

network_connection_pool* chassis_event_thread_pool(network_backend_t* backend) {
	guint index = GPOINTER_TO_UINT(g_private_get(&tls_index));
	return g_ptr_array_index(backend->pools, index);
}