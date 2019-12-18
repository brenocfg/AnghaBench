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
typedef  size_t uint32_t ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,size_t,size_t,size_t,size_t,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_SCHED_LOAD ; 
 int /*<<< orphan*/  MACH_SCHED_LOAD_EFFECTIVE ; 
 size_t MAX_LOAD ; 
 size_t SCHED_LOAD_EWMA_ALPHA_NEW ; 
 size_t SCHED_LOAD_EWMA_ALPHA_OLD ; 
 size_t SCHED_LOAD_EWMA_ALPHA_SHIFT ; 
 size_t SCHED_LOAD_EWMA_UNSCALE (size_t) ; 
 size_t TH_BUCKET_FIXPRI ; 
 int TH_BUCKET_MAX ; 
 size_t TH_BUCKET_RUN ; 
 size_t TH_BUCKET_SHARE_BG ; 
 size_t TH_BUCKET_SHARE_DF ; 
 size_t TH_BUCKET_SHARE_FG ; 
 size_t TH_BUCKET_SHARE_UT ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t processor_avail_count ; 
 size_t* sched_load ; 
 size_t* sched_run_buckets ; 

void
compute_sched_load(void)
{
	/*
	 * Retrieve a snapshot of the current run counts.
	 *
	 * Why not a bcopy()? Because we need atomic word-sized reads of sched_run_buckets,
	 * not byte-by-byte copy.
	 */
	uint32_t ncpus = processor_avail_count;
	uint32_t load_now[TH_BUCKET_MAX];

	load_now[TH_BUCKET_RUN]      = sched_run_buckets[TH_BUCKET_RUN];
	load_now[TH_BUCKET_FIXPRI]   = sched_run_buckets[TH_BUCKET_FIXPRI];
	load_now[TH_BUCKET_SHARE_FG] = sched_run_buckets[TH_BUCKET_SHARE_FG];
	load_now[TH_BUCKET_SHARE_DF] = sched_run_buckets[TH_BUCKET_SHARE_DF];
	load_now[TH_BUCKET_SHARE_UT] = sched_run_buckets[TH_BUCKET_SHARE_UT];
	load_now[TH_BUCKET_SHARE_BG] = sched_run_buckets[TH_BUCKET_SHARE_BG];

	assert(load_now[TH_BUCKET_RUN] >= 0);
	assert(load_now[TH_BUCKET_FIXPRI] >= 0);

	uint32_t nthreads = load_now[TH_BUCKET_RUN];
	uint32_t nfixpri  = load_now[TH_BUCKET_FIXPRI];

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	        MACHDBG_CODE(DBG_MACH_SCHED, MACH_SCHED_LOAD) | DBG_FUNC_NONE,
	        load_now[TH_BUCKET_FIXPRI], (load_now[TH_BUCKET_SHARE_FG] + load_now[TH_BUCKET_SHARE_DF]),
	        load_now[TH_BUCKET_SHARE_BG],   load_now[TH_BUCKET_SHARE_UT], 0);

	/*
	 * Compute the timeshare priority conversion factor based on loading.
	 * Because our counters may be incremented and accessed
	 * concurrently with respect to each other, we may have
	 * windows where the invariant (nthreads - nfixpri) == (fg + df + bg + ut)
	 * is broken, so truncate values in these cases.
	 */
	uint32_t timeshare_threads = (nthreads - nfixpri);
	for (uint32_t i = TH_BUCKET_SHARE_FG; i <= TH_BUCKET_SHARE_BG ; i++) {
		if (load_now[i] > timeshare_threads)
			load_now[i] = timeshare_threads;
	}

	/* 
	 * Default threads contribute up to (NCPUS * 2) of load to FG threads 
	 */
	if (load_now[TH_BUCKET_SHARE_DF] <= (ncpus * 2)) {
		load_now[TH_BUCKET_SHARE_FG] += load_now[TH_BUCKET_SHARE_DF];
	} else {
		load_now[TH_BUCKET_SHARE_FG] += (ncpus * 2);
	}
	
	/*
	 * Utility threads contribute up to NCPUS of load to FG & DF threads
	 */
	if (load_now[TH_BUCKET_SHARE_UT] <= ncpus) {
		load_now[TH_BUCKET_SHARE_FG] += load_now[TH_BUCKET_SHARE_UT];
		load_now[TH_BUCKET_SHARE_DF] += load_now[TH_BUCKET_SHARE_UT];
	} else {
		load_now[TH_BUCKET_SHARE_FG] += ncpus;
		load_now[TH_BUCKET_SHARE_DF] += ncpus;
	}

	/*
	 * BG threads contribute up to 1 thread worth of load to FG, DF and UT threads
	 */
	if (load_now[TH_BUCKET_SHARE_BG] > 0) {
		load_now[TH_BUCKET_SHARE_FG] += 1;
		load_now[TH_BUCKET_SHARE_DF] += 1;
		load_now[TH_BUCKET_SHARE_UT] += 1;
	}

	/*
	 * The conversion factor consists of two components:
	 * a fixed value based on the absolute time unit (sched_fixed_shift),
	 * and a dynamic portion based on load (sched_load_shifts).
	 *
	 * Zero load results in a out of range shift count.
	 */

	for (uint32_t i = TH_BUCKET_SHARE_FG; i <= TH_BUCKET_SHARE_BG ; i++) {
		uint32_t bucket_load = 0;

		if (load_now[i] > ncpus) {
			/* Normalize the load to number of CPUs */
			if (ncpus > 1)
				bucket_load = load_now[i] / ncpus;
			else
				bucket_load = load_now[i];

			if (bucket_load > MAX_LOAD)
				bucket_load = MAX_LOAD;
		}
		/* Plug the load values into the EWMA algorithm to calculate (scaled for fixpoint) sched_load */
		sched_load[i] = (sched_load[i] * SCHED_LOAD_EWMA_ALPHA_OLD) + ((bucket_load << SCHED_LOAD_EWMA_ALPHA_SHIFT) * SCHED_LOAD_EWMA_ALPHA_NEW);
		sched_load[i] = sched_load[i] >> SCHED_LOAD_EWMA_ALPHA_SHIFT;
	}

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	        MACHDBG_CODE(DBG_MACH_SCHED, MACH_SCHED_LOAD_EFFECTIVE) | DBG_FUNC_NONE, 
			SCHED_LOAD_EWMA_UNSCALE(sched_load[TH_BUCKET_SHARE_FG]), SCHED_LOAD_EWMA_UNSCALE(sched_load[TH_BUCKET_SHARE_DF]),
			SCHED_LOAD_EWMA_UNSCALE(sched_load[TH_BUCKET_SHARE_UT]), SCHED_LOAD_EWMA_UNSCALE(sched_load[TH_BUCKET_SHARE_BG]), 0);
}