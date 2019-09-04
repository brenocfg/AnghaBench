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
typedef  int /*<<< orphan*/  uint64_t ;
struct kpcdata {int counterc; int /*<<< orphan*/  running; int /*<<< orphan*/  configv; scalar_t__ configc; int /*<<< orphan*/  counterv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_INFO (int,int,...) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int KPC_MAX_COUNTERS ; 
 int PERF_KPC_THREAD_SAMPLE ; 
 int /*<<< orphan*/  kpc_get_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kpc_get_config_count (int /*<<< orphan*/ ) ; 
 scalar_t__ kpc_get_curthread_counters (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpc_get_running () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
kperf_kpc_thread_sample(struct kpcdata *kpcd, int sample_config)
{
	BUF_INFO(PERF_KPC_THREAD_SAMPLE | DBG_FUNC_START, sample_config);

	kpcd->running = kpc_get_running();
	/* let kpc_get_curthread_counters set the correct count */
	kpcd->counterc = KPC_MAX_COUNTERS;
	if (kpc_get_curthread_counters(&kpcd->counterc,
	                               kpcd->counterv)) {
		/* if thread counters aren't ready, default to 0 */
		memset(kpcd->counterv, 0,
		       sizeof(uint64_t) * kpcd->counterc);
	}
	/* help out Instruments by sampling KPC's config */
	if (!sample_config) {
		kpcd->configc = 0;
	} else {
		kpcd->configc = kpc_get_config_count(kpcd->running);
		kpc_get_config(kpcd->running, kpcd->configv);
	}

	BUF_INFO(PERF_KPC_THREAD_SAMPLE | DBG_FUNC_END, kpcd->running, kpcd->counterc);
}