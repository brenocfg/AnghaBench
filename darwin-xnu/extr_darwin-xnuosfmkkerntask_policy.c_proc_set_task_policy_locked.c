#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
struct task_requested_policy {int trp_ext_darwinbg; int trp_int_darwinbg; int trp_ext_iotier; int trp_ext_iopassive; int trp_int_iotier; int trp_int_iopassive; int trp_bg_iotier; int trp_tal_enabled; int trp_boosted; int trp_role; int trp_terminated; int trp_base_latency_qos; int trp_base_through_qos; int trp_sfi_managed; int trp_over_latency_qos; int trp_over_through_qos; } ;
struct TYPE_3__ {struct task_requested_policy requested_policy; } ;

/* Variables and functions */
#define  TASK_BASE_LATENCY_QOS_POLICY 141 
#define  TASK_BASE_THROUGHPUT_QOS_POLICY 140 
 int TASK_POLICY_ATTRIBUTE ; 
#define  TASK_POLICY_BASE_LATENCY_AND_THROUGHPUT_QOS 139 
#define  TASK_POLICY_BOOST 138 
#define  TASK_POLICY_DARWIN_BG 137 
#define  TASK_POLICY_DARWIN_BG_IOPOL 136 
 int TASK_POLICY_EXTERNAL ; 
 int TASK_POLICY_INTERNAL ; 
#define  TASK_POLICY_IO 135 
#define  TASK_POLICY_IOPOL 134 
#define  TASK_POLICY_OVERRIDE_LATENCY_AND_THROUGHPUT_QOS 133 
#define  TASK_POLICY_PASSIVE_IO 132 
#define  TASK_POLICY_ROLE 131 
#define  TASK_POLICY_SFI_MANAGED 130 
#define  TASK_POLICY_TAL 129 
#define  TASK_POLICY_TERMINATED 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  panic (char*,int,int,int,int) ; 
 int /*<<< orphan*/  proc_iopol_to_tier (int,int*,int*) ; 

__attribute__((used)) static void
proc_set_task_policy_locked(task_t      task,
                            int         category,
                            int         flavor,
                            int         value,
                            int         value2)
{
	int tier, passive;

	struct task_requested_policy requested = task->requested_policy;

	switch (flavor) {

	/* Category: EXTERNAL and INTERNAL */

		case TASK_POLICY_DARWIN_BG:
			if (category == TASK_POLICY_EXTERNAL)
				requested.trp_ext_darwinbg = value;
			else
				requested.trp_int_darwinbg = value;
			break;

		case TASK_POLICY_IOPOL:
			proc_iopol_to_tier(value, &tier, &passive);
			if (category == TASK_POLICY_EXTERNAL) {
				requested.trp_ext_iotier  = tier;
				requested.trp_ext_iopassive = passive;
			} else {
				requested.trp_int_iotier  = tier;
				requested.trp_int_iopassive = passive;
			}
			break;

		case TASK_POLICY_IO:
			if (category == TASK_POLICY_EXTERNAL)
				requested.trp_ext_iotier = value;
			else
				requested.trp_int_iotier = value;
			break;

		case TASK_POLICY_PASSIVE_IO:
			if (category == TASK_POLICY_EXTERNAL)
				requested.trp_ext_iopassive = value;
			else
				requested.trp_int_iopassive = value;
			break;

	/* Category: INTERNAL */

		case TASK_POLICY_DARWIN_BG_IOPOL:
			assert(category == TASK_POLICY_INTERNAL);
			proc_iopol_to_tier(value, &tier, &passive);
			requested.trp_bg_iotier = tier;
			break;

	/* Category: ATTRIBUTE */

		case TASK_POLICY_TAL:
			assert(category == TASK_POLICY_ATTRIBUTE);
			requested.trp_tal_enabled = value;
			break;

		case TASK_POLICY_BOOST:
			assert(category == TASK_POLICY_ATTRIBUTE);
			requested.trp_boosted = value;
			break;

		case TASK_POLICY_ROLE:
			assert(category == TASK_POLICY_ATTRIBUTE);
			requested.trp_role = value;
			break;

		case TASK_POLICY_TERMINATED:
			assert(category == TASK_POLICY_ATTRIBUTE);
			requested.trp_terminated = value;
			break;

		case TASK_BASE_LATENCY_QOS_POLICY:
			assert(category == TASK_POLICY_ATTRIBUTE);
			requested.trp_base_latency_qos = value;
			break;

		case TASK_BASE_THROUGHPUT_QOS_POLICY:
			assert(category == TASK_POLICY_ATTRIBUTE);
			requested.trp_base_through_qos = value;
			break;

		case TASK_POLICY_SFI_MANAGED:
			assert(category == TASK_POLICY_ATTRIBUTE);
			requested.trp_sfi_managed = value;
			break;

		case TASK_POLICY_BASE_LATENCY_AND_THROUGHPUT_QOS:
			assert(category == TASK_POLICY_ATTRIBUTE);
			requested.trp_base_latency_qos = value;
			requested.trp_base_through_qos = value2;
			break;

		case TASK_POLICY_OVERRIDE_LATENCY_AND_THROUGHPUT_QOS:
			assert(category == TASK_POLICY_ATTRIBUTE);
			requested.trp_over_latency_qos = value;
			requested.trp_over_through_qos = value2;
			break;

		default:
			panic("unknown task policy: %d %d %d %d", category, flavor, value, value2);
			break;
	}

	task->requested_policy = requested;
}