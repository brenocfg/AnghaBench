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
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 unsigned long long FIXED_RELOAD (int /*<<< orphan*/ ) ; 
 unsigned long long FIXED_SHADOW (int /*<<< orphan*/ ) ; 
 unsigned long long IA32_FIXED_CTRx (int) ; 
 int /*<<< orphan*/  MSR_IA32_PERF_GLOBAL_STATUS ; 
 int /*<<< orphan*/  ctr ; 
 int kpc_fixed_count () ; 
 unsigned long long kpc_fixed_max () ; 
 unsigned long long rdmsr64 (int /*<<< orphan*/ ) ; 

int
kpc_get_fixed_counters(uint64_t *counterv)
{
	int i, n = kpc_fixed_count();

#ifdef FIXED_COUNTER_SHADOW
	uint64_t status;

	/* snap the counters */
	for( i = 0; i < n; i++ ) {
		counterv[i] = FIXED_SHADOW(ctr) +
			(IA32_FIXED_CTRx(i) - FIXED_RELOAD(ctr));
	}

	/* Grab the overflow bits */
	status = rdmsr64(MSR_IA32_PERF_GLOBAL_STATUS);

	/* If the overflow bit is set for a counter, our previous read may or may not have been
	 * before the counter overflowed. Re-read any counter with it's overflow bit set so
	 * we know for sure that it has overflowed. The reason this matters is that the math
	 * is different for a counter that has overflowed. */
	for( i = 0; i < n; i++ ) {
		if ((1ull << (i + 32)) & status)
			counterv[i] = FIXED_SHADOW(ctr) +
				(kpc_fixed_max() - FIXED_RELOAD(ctr) + 1 /* Wrap */) + IA32_FIXED_CTRx(i);
	}
#else
	for( i = 0; i < n; i++ )
		counterv[i] = IA32_FIXED_CTRx(i);
#endif

	return 0;
}