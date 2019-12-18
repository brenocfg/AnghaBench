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
typedef  int /*<<< orphan*/  u64 ;
struct p4_pebs_bind {scalar_t__ metric_vert; scalar_t__ metric_pebs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  MSR_IA32_PEBS_ENABLE ; 
 int /*<<< orphan*/  MSR_P4_PEBS_MATRIX_VERT ; 
 scalar_t__ P4_PEBS_CONFIG_METRIC_MASK ; 
 scalar_t__ P4_PEBS_METRIC__max ; 
 unsigned int P4_PEBS_METRIC__none ; 
 int /*<<< orphan*/  checking_wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int p4_config_unpack_metric (int /*<<< orphan*/ ) ; 
 struct p4_pebs_bind* p4_pebs_bind_map ; 

__attribute__((used)) static void p4_pmu_enable_pebs(u64 config)
{
	struct p4_pebs_bind *bind;
	unsigned int idx;

	BUILD_BUG_ON(P4_PEBS_METRIC__max > P4_PEBS_CONFIG_METRIC_MASK);

	idx = p4_config_unpack_metric(config);
	if (idx == P4_PEBS_METRIC__none)
		return;

	bind = &p4_pebs_bind_map[idx];

	(void)checking_wrmsrl(MSR_IA32_PEBS_ENABLE,	(u64)bind->metric_pebs);
	(void)checking_wrmsrl(MSR_P4_PEBS_MATRIX_VERT,	(u64)bind->metric_vert);
}