#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* dtvs_state; } ;
typedef  TYPE_1__ dtrace_vstate_t ;
struct TYPE_13__ {size_t* dts_options; } ;
typedef  TYPE_2__ dtrace_state_t ;
struct TYPE_14__ {int dtms_access; } ;
typedef  TYPE_3__ dtrace_mstate_t ;
struct TYPE_15__ {int dtdt_flags; scalar_t__ dtdt_kind; size_t dtdt_size; } ;
typedef  TYPE_4__ dtrace_diftype_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DIF_TF_BYREF ; 
 scalar_t__ DIF_TYPE_STRING ; 
 size_t DTRACEOPT_STRSIZE ; 
 int DTRACE_ACCESS_KERNEL ; 
 int /*<<< orphan*/  DTRACE_RANGE_REMAIN (size_t*,uintptr_t,void*,size_t) ; 
 int dtrace_canload_remains (uintptr_t,size_t,size_t*,TYPE_3__*,TYPE_1__*) ; 
 int dtrace_strcanload (uintptr_t,size_t,size_t*,TYPE_3__*,TYPE_1__*) ; 
 size_t dtrace_strsize_default ; 

__attribute__((used)) static int
dtrace_vcanload(void *src, dtrace_diftype_t *type, size_t *remain,
	dtrace_mstate_t *mstate, dtrace_vstate_t *vstate)
{
	size_t sz;
	ASSERT(type->dtdt_flags & DIF_TF_BYREF);

	/*
	 * Calculate the max size before performing any checks since even
	 * DTRACE_ACCESS_KERNEL-credentialed callers expect that this function
	 * return the max length via 'remain'.
	 */
	if (type->dtdt_kind == DIF_TYPE_STRING) {
		dtrace_state_t *state = vstate->dtvs_state;

		if (state != NULL) {
			sz = state->dts_options[DTRACEOPT_STRSIZE];
		} else {
			/*
			 * In helper context, we have a NULL state; fall back
			 * to using the system-wide default for the string size
			 * in this case.
			 */
			sz = dtrace_strsize_default;
		}
	} else {
		sz = type->dtdt_size;
	}

	/*
	 * If we hold the privilege to read from kernel memory, then
	 * everything is readable.
	 */
	if ((mstate->dtms_access & DTRACE_ACCESS_KERNEL) != 0) {
		DTRACE_RANGE_REMAIN(remain, (uintptr_t)src, src, sz);
		return (1);
	}

	if (type->dtdt_kind == DIF_TYPE_STRING) {
		return (dtrace_strcanload((uintptr_t)src, sz, remain, mstate,
			vstate));
	}
	return (dtrace_canload_remains((uintptr_t)src, sz, remain, mstate,
		vstate));
}