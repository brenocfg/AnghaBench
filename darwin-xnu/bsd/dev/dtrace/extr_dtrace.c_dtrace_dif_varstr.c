#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/ * dts_options; } ;
typedef  TYPE_1__ dtrace_state_t ;
struct TYPE_6__ {int dtms_access; size_t dtms_scratch_ptr; size_t dtms_scratch_base; size_t dtms_scratch_size; } ;
typedef  TYPE_2__ dtrace_mstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_NOSCRATCH ; 
 size_t DTRACEOPT_STRSIZE ; 
 int DTRACE_ACCESS_KERNEL ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_strcpy (void const*,void*,size_t) ; 
 int dtrace_strlen (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
uintptr_t
dtrace_dif_varstr(uintptr_t addr, dtrace_state_t *state,
    dtrace_mstate_t *mstate)
{
	uint64_t size = state->dts_options[DTRACEOPT_STRSIZE];
	uintptr_t ret;
	size_t strsz;

	/*
	 * The easy case: this probe is allowed to read all of memory, so
	 * we can just return this as a vanilla pointer.
	 */
	if ((mstate->dtms_access & DTRACE_ACCESS_KERNEL) != 0)
		return (addr);

	/*
	 * This is the tougher case: we copy the string in question from
	 * kernel memory into scratch memory and return it that way: this
	 * ensures that we won't trip up when access checking tests the
	 * BYREF return value.
	 */
	strsz = dtrace_strlen((char *)addr, size) + 1;

	if (mstate->dtms_scratch_ptr + strsz >
	    mstate->dtms_scratch_base + mstate->dtms_scratch_size) {
		DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
		return (0);
	}

	dtrace_strcpy((const void *)addr, (void *)mstate->dtms_scratch_ptr,
	    strsz);
	ret = mstate->dtms_scratch_ptr;
	mstate->dtms_scratch_ptr += strsz;
	return (ret);
}