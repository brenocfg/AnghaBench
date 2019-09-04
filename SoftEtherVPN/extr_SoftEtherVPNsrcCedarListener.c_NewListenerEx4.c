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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  THREAD_PROC ;
typedef  int /*<<< orphan*/  LISTENER ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * NewListenerEx5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int,int,int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int) ; 

LISTENER *NewListenerEx4(CEDAR *cedar, UINT proto, UINT port, THREAD_PROC *proc, void *thread_param, bool local_only, bool shadow_ipv6,
						 volatile UINT *natt_global_udp_port, UCHAR rand_port_id)
{
	return NewListenerEx5(cedar, proto, port, proc, thread_param,
		local_only, shadow_ipv6, natt_global_udp_port, rand_port_id, false);
}