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
struct proc {int p_pid; int p_csflags; int /*<<< orphan*/  task; int /*<<< orphan*/  p_mlock; } ;

/* Variables and functions */
 int CS_DEBUGGED ; 
 int CS_HARD ; 
 int CS_KILL ; 
 int CS_VALID ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 scalar_t__ cs_debug ; 
 int /*<<< orphan*/  get_task_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mac_proc_check_run_cs_invalid (struct proc*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  proc_lock (struct proc*) ; 
 int /*<<< orphan*/  proc_unlock (struct proc*) ; 
 int /*<<< orphan*/  vm_map_switch_protect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cs_allow_invalid(struct proc *p)
{
#if MACH_ASSERT
	lck_mtx_assert(&p->p_mlock, LCK_MTX_ASSERT_NOTOWNED);
#endif
#if CONFIG_MACF
	/* There needs to be a MAC policy to implement this hook, or else the
	 * kill bits will be cleared here every time. If we have 
	 * CONFIG_ENFORCE_SIGNED_CODE, we can assume there is a policy
	 * implementing the hook. 
	 */
	if( 0 != mac_proc_check_run_cs_invalid(p)) {
		if(cs_debug) printf("CODE SIGNING: cs_allow_invalid() "
				    "not allowed: pid %d\n", 
				    p->p_pid);
		return 0;
	}
	if(cs_debug) printf("CODE SIGNING: cs_allow_invalid() "
			    "allowed: pid %d\n", 
			    p->p_pid);
	proc_lock(p);
	p->p_csflags &= ~(CS_KILL | CS_HARD);
	if (p->p_csflags & CS_VALID)
	{
		p->p_csflags |= CS_DEBUGGED;
	}
	
	proc_unlock(p);
	
	vm_map_switch_protect(get_task_map(p->task), FALSE);
#endif
	return (p->p_csflags & (CS_KILL | CS_HARD)) == 0;
}