#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
struct TYPE_5__ {TYPE_1__* task; } ;
struct TYPE_4__ {int /*<<< orphan*/  effective_policy; } ;

/* Variables and functions */

uintptr_t
theffective_1(thread_t thread)
{
#if defined __LP64__
	return *(uintptr_t*)&thread->task->effective_policy;
#else
	uintptr_t* raw = (uintptr_t*)(void*)&thread->effective_policy;
	return raw[1];
#endif
}