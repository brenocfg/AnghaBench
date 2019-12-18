#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* srv; } ;
typedef  TYPE_2__ network_mysqld_con ;
typedef  int /*<<< orphan*/  network_backends_t ;
struct TYPE_9__ {scalar_t__ type; scalar_t__ state; } ;
typedef  TYPE_3__ network_backend_t ;
typedef  int guint ;
struct TYPE_7__ {int /*<<< orphan*/ * backends; } ;

/* Variables and functions */
 scalar_t__ BACKEND_STATE_UP ; 
 scalar_t__ BACKEND_TYPE_RW ; 
 int /*<<< orphan*/ * chassis_event_thread_pool (TYPE_3__*) ; 
 int network_backends_count (int /*<<< orphan*/ *) ; 
 TYPE_3__* network_backends_get (int /*<<< orphan*/ *,int) ; 

int idle_rw(network_mysqld_con* con) {
	int ret = -1;
	guint i;

	network_backends_t* backends = con->srv->backends;

	guint count = network_backends_count(backends);
	for (i = 0; i < count; ++i) {
		network_backend_t* backend = network_backends_get(backends, i);
		if (backend == NULL) continue;

		if (chassis_event_thread_pool(backend) == NULL) continue;

		if (backend->type == BACKEND_TYPE_RW && backend->state == BACKEND_STATE_UP) {
			ret = i;
			break;
		}
	}

	return ret;
}