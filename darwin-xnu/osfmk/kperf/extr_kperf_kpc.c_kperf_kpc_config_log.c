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
struct kpcdata {int /*<<< orphan*/  configc; int /*<<< orphan*/  counterc; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KPC_CLASS_FIXED_MASK ; 
 int /*<<< orphan*/  PERF_KPC_CONFIG ; 
 int /*<<< orphan*/  kpc_get_counter_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kperf_kpc_config_log(const struct kpcdata *kpcd)
{
	BUF_DATA(PERF_KPC_CONFIG,
	         kpcd->running,
	         kpcd->counterc,
	         kpc_get_counter_count(KPC_CLASS_FIXED_MASK),
	         kpcd->configc);
}