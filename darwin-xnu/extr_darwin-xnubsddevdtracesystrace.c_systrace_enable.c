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
struct TYPE_4__ {scalar_t__ sy_callc; } ;
struct TYPE_3__ {scalar_t__ stsy_entry; scalar_t__ stsy_return; scalar_t__ stsy_underlying; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DTRACE_IDNONE ; 
 scalar_t__ SYSTRACE_ISENTRY (uintptr_t) ; 
 int SYSTRACE_SYSNUM (uintptr_t) ; 
 int /*<<< orphan*/  dtrace_systrace_lock ; 
 scalar_t__ dtrace_systrace_syscall ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ml_nofault_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* sysent ; 
 TYPE_1__* systrace_sysent ; 

__attribute__((used)) static int
systrace_enable(void *arg, dtrace_id_t id, void *parg)
{
#pragma unused(arg) /* __APPLE__ */
    
	int sysnum = SYSTRACE_SYSNUM((uintptr_t)parg);
	int enabled = (systrace_sysent[sysnum].stsy_entry != DTRACE_IDNONE ||
	    systrace_sysent[sysnum].stsy_return != DTRACE_IDNONE);

	if (SYSTRACE_ISENTRY((uintptr_t)parg)) {
		systrace_sysent[sysnum].stsy_entry = id;
	} else {
		systrace_sysent[sysnum].stsy_return = id;
	}

	if (enabled) {
		ASSERT(sysent[sysnum].sy_callc == dtrace_systrace_syscall);
		return(0);
	}

	lck_mtx_lock(&dtrace_systrace_lock);
	if (sysent[sysnum].sy_callc == systrace_sysent[sysnum].stsy_underlying) {
		vm_offset_t dss = (vm_offset_t)&dtrace_systrace_syscall;
		ml_nofault_copy((vm_offset_t)&dss, (vm_offset_t)&sysent[sysnum].sy_callc, sizeof(vm_offset_t));
	}
	lck_mtx_unlock(&dtrace_systrace_lock);
	return (0);
}