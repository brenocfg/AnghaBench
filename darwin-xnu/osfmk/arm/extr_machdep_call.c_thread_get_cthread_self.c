#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  uintptr_t vm_address_t ;
typedef  uintptr_t kern_return_t ;
struct TYPE_3__ {uintptr_t cthread_self; } ;
struct TYPE_4__ {TYPE_1__ machine; } ;

/* Variables and functions */
 uintptr_t MACHDEP_CTHREAD_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* current_thread () ; 
 uintptr_t get_tpidrro () ; 

vm_address_t
thread_get_cthread_self(void)
{
	uintptr_t	self;

	self = get_tpidrro();
#if __arm__
	self &= ~3;
	assert( self == current_thread()->machine.cthread_self);
	return ((kern_return_t) current_thread()->machine.cthread_self);
#else
	self &= MACHDEP_CTHREAD_MASK;
	assert( self == current_thread()->machine.cthread_self);
	return self;
#endif
}