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
struct kpcdata {int /*<<< orphan*/  counterc; int /*<<< orphan*/  running; int /*<<< orphan*/  configv; scalar_t__ configc; int /*<<< orphan*/  counterv; int /*<<< orphan*/  curcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_INFO (int,int,...) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int PERF_KPC_CPU_SAMPLE ; 
 int /*<<< orphan*/  kpc_get_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kpc_get_config_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpc_get_cpu_counters (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpc_get_running () ; 

void
kperf_kpc_cpu_sample(struct kpcdata *kpcd, int sample_config)
{
	BUF_INFO(PERF_KPC_CPU_SAMPLE | DBG_FUNC_START, sample_config);

	kpcd->running  = kpc_get_running();
	kpcd->counterc = kpc_get_cpu_counters(0, kpcd->running,
	                                      &kpcd->curcpu,
	                                      kpcd->counterv);
	if (!sample_config) {
		kpcd->configc = 0;
	} else {
		kpcd->configc = kpc_get_config_count(kpcd->running);
		kpc_get_config(kpcd->running, kpcd->configv);
	}

	BUF_INFO(PERF_KPC_CPU_SAMPLE | DBG_FUNC_END, kpcd->running, kpcd->counterc);
}