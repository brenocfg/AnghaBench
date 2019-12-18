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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
struct TYPE_4__ {int dtms_access; } ;
typedef  TYPE_1__ dtrace_mstate_t ;

/* Variables and functions */
 int DTRACE_ACCESS_KERNEL ; 
 int /*<<< orphan*/  DTRACE_RANGE_REMAIN (size_t*,scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  MIN (size_t,size_t) ; 
 scalar_t__ dtrace_canload_remains (scalar_t__,int /*<<< orphan*/ ,size_t*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int dtrace_strlen (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_strcanload(uint64_t addr, size_t sz, size_t *remain,
	dtrace_mstate_t *mstate, dtrace_vstate_t *vstate)
{
	size_t rsize;

	/*
	 * If we hold the privilege to read from kernel memory, then
	 * everything is readable.
	 */
	if ((mstate->dtms_access & DTRACE_ACCESS_KERNEL) != 0) {
		DTRACE_RANGE_REMAIN(remain, addr, addr, sz);
		return (1);
	}

	/*
	 * Even if the caller is uninterested in querying the remaining valid
	 * range, it is required to ensure that the access is allowed.
	 */
	if (remain == NULL) {
		remain = &rsize;
	}
	if (dtrace_canload_remains(addr, 0, remain, mstate, vstate)) {
		size_t strsz;
		/*
		 * Perform the strlen after determining the length of the
		 * memory region which is accessible.  This prevents timing
		 * information from being used to find NULs in memory which is
		 * not accessible to the caller.
		 */
		strsz = 1 + dtrace_strlen((char *)(uintptr_t)addr,
			MIN(sz, *remain));
		if (strsz <= *remain) {
			return (1);
		}
	}

	return (0);
}