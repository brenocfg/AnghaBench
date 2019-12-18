#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct TYPE_4__ {scalar_t__ suspend_parked; int /*<<< orphan*/  suspend_count; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  thread_set_apc_ast (TYPE_1__*) ; 

void
thread_hold(thread_t thread)
{
	if (thread->suspend_count++ == 0) {
		thread_set_apc_ast(thread);
		assert(thread->suspend_parked == FALSE);
	}
}