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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/ * host_priv_t ;
typedef  int boolean_t ;
struct TYPE_4__ {int options; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int TH_OPT_VMPRIV ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  realhost ; 
 int /*<<< orphan*/  vm_page_free_reserve (int) ; 

kern_return_t
thread_wire_internal(
	host_priv_t		host_priv,
	thread_t		thread,
	boolean_t		wired,
	boolean_t		*prev_state)
{
	if (host_priv == NULL || thread != current_thread())
		return (KERN_INVALID_ARGUMENT);

	assert(host_priv == &realhost);

	if (prev_state)
	    *prev_state = (thread->options & TH_OPT_VMPRIV) != 0;
	
	if (wired) {
	    if (!(thread->options & TH_OPT_VMPRIV)) 
		    vm_page_free_reserve(1);	/* XXX */
	    thread->options |= TH_OPT_VMPRIV;
	}
	else {
	    if (thread->options & TH_OPT_VMPRIV) 
		    vm_page_free_reserve(-1);	/* XXX */
	    thread->options &= ~TH_OPT_VMPRIV;
	}

	return (KERN_SUCCESS);
}