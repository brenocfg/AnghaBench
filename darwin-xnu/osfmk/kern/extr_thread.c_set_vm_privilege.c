#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {int options; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int TH_OPT_VMPRIV ; 
 scalar_t__ TRUE ; 
 TYPE_1__* current_thread () ; 

boolean_t
set_vm_privilege(boolean_t privileged)
{
	boolean_t       was_vmpriv;

	if (current_thread()->options & TH_OPT_VMPRIV)
		was_vmpriv = TRUE;
	else
		was_vmpriv = FALSE;

	if (privileged != FALSE)
		current_thread()->options |= TH_OPT_VMPRIV;
	else
		current_thread()->options &= ~TH_OPT_VMPRIV;

	return (was_vmpriv);
}