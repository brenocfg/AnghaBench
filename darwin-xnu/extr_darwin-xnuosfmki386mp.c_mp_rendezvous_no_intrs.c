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

/* Variables and functions */
 int /*<<< orphan*/  mp_rendezvous (int /*<<< orphan*/ ,void (*) (void*),int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  setup_disable_intrs ; 
 int /*<<< orphan*/  teardown_restore_intrs ; 

void
mp_rendezvous_no_intrs(
	      void (*action_func)(void *),
	      void *arg)
{
	mp_rendezvous(setup_disable_intrs,
		      action_func,
		      teardown_restore_intrs,
		      arg);	
}