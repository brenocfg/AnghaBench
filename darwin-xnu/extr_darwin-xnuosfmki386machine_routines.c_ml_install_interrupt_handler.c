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
typedef  int /*<<< orphan*/  boolean_t ;
typedef  scalar_t__ IOInterruptHandler ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PE_install_interrupt_handler (void*,int,void*,scalar_t__,void*) ; 
 int /*<<< orphan*/  initialize_screen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kPEAcquireScreen ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 

void ml_install_interrupt_handler(
	void *nub,
	int source,
	void *target,
	IOInterruptHandler handler,
	void *refCon)  
{
	boolean_t current_state;

	current_state = ml_set_interrupts_enabled(FALSE);

	PE_install_interrupt_handler(nub, source, target,
	                             (IOInterruptHandler) handler, refCon);

	(void) ml_set_interrupts_enabled(current_state);

	initialize_screen(NULL, kPEAcquireScreen);
}