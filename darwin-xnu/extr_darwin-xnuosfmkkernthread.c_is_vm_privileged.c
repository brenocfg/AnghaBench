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
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int options; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int TH_OPT_VMPRIV ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* current_thread () ; 

boolean_t
is_vm_privileged(void)
{
	return current_thread()->options & TH_OPT_VMPRIV ? TRUE : FALSE;
}