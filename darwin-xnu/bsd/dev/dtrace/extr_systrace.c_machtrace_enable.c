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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  void* dtrace_id_t ;
struct TYPE_4__ {void* mach_trap_function; } ;
struct TYPE_3__ {scalar_t__ stsy_entry; scalar_t__ stsy_return; void* stsy_underlying; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DTRACE_IDNONE ; 
 scalar_t__ SYSTRACE_ISENTRY (uintptr_t) ; 
 int SYSTRACE_SYSNUM (uintptr_t) ; 
 scalar_t__ dtrace_machtrace_syscall ; 
 int /*<<< orphan*/  dtrace_systrace_lock ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* mach_trap_table ; 
 TYPE_1__* machtrace_sysent ; 
 int /*<<< orphan*/  ml_nofault_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
machtrace_enable(void *arg, dtrace_id_t id, void *parg)
{
#pragma unused(arg) /* __APPLE__ */
    
	int sysnum = SYSTRACE_SYSNUM((uintptr_t)parg);
	int enabled = (machtrace_sysent[sysnum].stsy_entry != DTRACE_IDNONE ||
			machtrace_sysent[sysnum].stsy_return != DTRACE_IDNONE);

	if (SYSTRACE_ISENTRY((uintptr_t)parg)) {
		machtrace_sysent[sysnum].stsy_entry = id;
	} else {
		machtrace_sysent[sysnum].stsy_return = id;
	}

	if (enabled) {
	    ASSERT(mach_trap_table[sysnum].mach_trap_function == (void *)dtrace_machtrace_syscall);
	    return(0);
	}

	lck_mtx_lock(&dtrace_systrace_lock);

	if (mach_trap_table[sysnum].mach_trap_function == machtrace_sysent[sysnum].stsy_underlying) {
		vm_offset_t dss = (vm_offset_t)&dtrace_machtrace_syscall;
		ml_nofault_copy((vm_offset_t)&dss, (vm_offset_t)&mach_trap_table[sysnum].mach_trap_function, sizeof(vm_offset_t));
	}

	lck_mtx_unlock(&dtrace_systrace_lock);

	return(0);
}