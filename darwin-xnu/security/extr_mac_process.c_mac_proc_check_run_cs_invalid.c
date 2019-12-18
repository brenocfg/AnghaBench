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
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_vm_enforce ; 
 int /*<<< orphan*/  proc_check_run_cs_invalid ; 

int
mac_proc_check_run_cs_invalid(proc_t proc)
{
	int error;
	
#if SECURITY_MAC_CHECK_ENFORCE
    /* 21167099 - only check if we allow write */
    if (!mac_vm_enforce)
        return 0;
#endif
	
	MAC_CHECK(proc_check_run_cs_invalid, proc);
	
	return (error);
}