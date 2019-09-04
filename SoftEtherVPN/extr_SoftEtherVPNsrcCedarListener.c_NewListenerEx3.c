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
typedef  int /*<<< orphan*/  THREAD_PROC ;
typedef  int /*<<< orphan*/  LISTENER ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * NewListenerEx4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

LISTENER *NewListenerEx3(CEDAR *cedar, UINT proto, UINT port, THREAD_PROC *proc, void *thread_param, bool local_only, bool shadow_ipv6)
{
	return NewListenerEx4(cedar, proto, port, proc, thread_param, local_only, shadow_ipv6, NULL, 0);
}