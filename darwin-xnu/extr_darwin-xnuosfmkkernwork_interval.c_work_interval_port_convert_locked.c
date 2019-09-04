#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct work_interval {int dummy; } ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_6__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 scalar_t__ IKOT_WORK_INTERVAL ; 
 int /*<<< orphan*/  IP_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_active (TYPE_1__*) ; 
 scalar_t__ ip_kotype (TYPE_1__*) ; 
 int /*<<< orphan*/  wi_retain (struct work_interval*) ; 

__attribute__((used)) static struct work_interval *
work_interval_port_convert_locked(ipc_port_t port)
{
	struct work_interval *work_interval = NULL;

	if (!IP_VALID(port))
		return NULL;

	if (!ip_active(port))
		return NULL;

	if (IKOT_WORK_INTERVAL != ip_kotype(port))
		return NULL;

	work_interval = (struct work_interval *)port->ip_kobject;

	wi_retain(work_interval);

	return work_interval;
}