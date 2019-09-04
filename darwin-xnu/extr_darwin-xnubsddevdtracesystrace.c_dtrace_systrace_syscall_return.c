#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uthread_t ;
typedef  int user_addr_t ;
typedef  int uint64_t ;
typedef  int u_int64_t ;
typedef  int u_int ;
struct TYPE_5__ {int stsy_return_type; int /*<<< orphan*/  stsy_return; } ;
typedef  TYPE_2__ systrace_sysent_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;
struct TYPE_4__ {int t_dtrace_errno; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_IDNONE ; 
 int EJUSTRETURN ; 
 int ERESTART ; 
 size_t SYS_invalid ; 
#define  _SYSCALL_RET_ADDR_T 135 
#define  _SYSCALL_RET_INT_T 134 
#define  _SYSCALL_RET_NONE 133 
#define  _SYSCALL_RET_OFF_T 132 
#define  _SYSCALL_RET_SIZE_T 131 
#define  _SYSCALL_RET_SSIZE_T 130 
#define  _SYSCALL_RET_UINT64_T 129 
#define  _SYSCALL_RET_UINT_T 128 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 unsigned short nsysent ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systrace_probe (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* systrace_sysent ; 

void
dtrace_systrace_syscall_return(unsigned short code, int rval, int *rv)
{
	systrace_sysent_t *sy;
	dtrace_id_t id;

	// Bounds "check" the value of code a la unix_syscall_return
	sy = (code >= nsysent) ? &systrace_sysent[SYS_invalid] : &systrace_sysent[code];

	if ((id = sy->stsy_return) != DTRACE_IDNONE) {
		uint64_t munged_rv0, munged_rv1;
    	uthread_t uthread = (uthread_t)get_bsdthread_info(current_thread());

		if (uthread)
			uthread->t_dtrace_errno = rval; /* Establish t_dtrace_errno now in case this enabling refers to it. */

		/*
	 	 * "Decode" rv for use in the call to dtrace_probe()
	 	 */
		if (rval == ERESTART) {
			munged_rv0 = -1LL; /* System call will be reissued in user mode. Make DTrace report a -1 return. */
			munged_rv1 = -1LL;
		} else if (rval != EJUSTRETURN) {
			if (rval) {
				munged_rv0 = -1LL; /* Mimic what libc will do. */
				munged_rv1 = -1LL;
			} else {
				switch (sy->stsy_return_type) {
				case _SYSCALL_RET_INT_T:
					munged_rv0 = rv[0];
					munged_rv1 = rv[1];
					break;
				case _SYSCALL_RET_UINT_T:
					munged_rv0 = ((u_int)rv[0]);
					munged_rv1 = ((u_int)rv[1]);
					break;
				case _SYSCALL_RET_OFF_T:
				case _SYSCALL_RET_UINT64_T:
					munged_rv0 = *(u_int64_t *)rv;
					munged_rv1 = 0LL;
					break;
				case _SYSCALL_RET_ADDR_T:
				case _SYSCALL_RET_SIZE_T:
				case _SYSCALL_RET_SSIZE_T:
					munged_rv0 = *(user_addr_t *)rv;
					munged_rv1 = 0LL;
					break;
				case _SYSCALL_RET_NONE:
					munged_rv0 = 0LL;
					munged_rv1 = 0LL;
					break;
				default:
					munged_rv0 = 0LL;
					munged_rv1 = 0LL;
					break;
				}
			}
		} else {
			munged_rv0 = 0LL;
			munged_rv1 = 0LL;
		}

		(*systrace_probe)(id, munged_rv0, munged_rv0, munged_rv1, (uint64_t)rval, 0);
	}
}