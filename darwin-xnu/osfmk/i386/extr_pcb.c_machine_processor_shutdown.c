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
typedef  int /*<<< orphan*/  thread_t ;
typedef  TYPE_1__* processor_t ;
struct TYPE_6__ {int /*<<< orphan*/  idle_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  Shutdown_context (int /*<<< orphan*/ ,void (*) (TYPE_1__*),TYPE_1__*) ; 
 int /*<<< orphan*/  cpu_number () ; 
 int /*<<< orphan*/  fpu_switch_context (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_switch_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_suspend () ; 

thread_t        
machine_processor_shutdown(
	thread_t	thread,
	void		(*doshutdown)(processor_t),
	processor_t	processor)
{
#if CONFIG_VMX
	vmx_suspend();
#endif
	fpu_switch_context(thread, NULL);
	pmap_switch_context(thread, processor->idle_thread, cpu_number());
	return(Shutdown_context(thread, doshutdown, processor));
}