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
struct kpcdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_KPC_DATA ; 
 int /*<<< orphan*/  PERF_KPC_DATA32 ; 
 int /*<<< orphan*/  kperf_kpc_config_log (struct kpcdata const*) ; 
 int /*<<< orphan*/  kperf_kpc_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kpcdata const*) ; 

void
kperf_kpc_cpu_log(const struct kpcdata *kpcd)
{
	kperf_kpc_config_log(kpcd);
	kperf_kpc_log(PERF_KPC_DATA, PERF_KPC_DATA32, kpcd);
}