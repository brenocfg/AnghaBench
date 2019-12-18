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
typedef  int uint64_t ;
typedef  TYPE_1__* task_t ;
struct task_effective_policy {scalar_t__ tep_qos_ceiling; scalar_t__ tep_sfi_managed; scalar_t__ tep_through_qos; scalar_t__ tep_latency_qos; scalar_t__ tep_role; scalar_t__ tep_suppressed_cpu; scalar_t__ tep_sup_active; scalar_t__ tep_watchers_bg; scalar_t__ tep_tal_engaged; scalar_t__ tep_qos_ui_is_urgent; scalar_t__ tep_bg_iotier; scalar_t__ tep_new_sockets_bg; scalar_t__ tep_all_sockets_bg; scalar_t__ tep_terminated; scalar_t__ tep_lowpri_cpu; scalar_t__ tep_darwinbg; scalar_t__ tep_io_passive; scalar_t__ tep_io_tier; } ;
struct TYPE_3__ {struct task_effective_policy effective_policy; } ;

/* Variables and functions */
 int POLICY_EFF_ALL_SOCKETS_BG ; 
 int POLICY_EFF_BG_IOTIER_SHIFT ; 
 int POLICY_EFF_DARWIN_BG ; 
 int POLICY_EFF_IO_PASSIVE ; 
 int POLICY_EFF_IO_TIER_SHIFT ; 
 int POLICY_EFF_LATENCY_QOS_SHIFT ; 
 int POLICY_EFF_LOWPRI_CPU ; 
 int POLICY_EFF_NEW_SOCKETS_BG ; 
 int POLICY_EFF_QOS_CEILING_SHIFT ; 
 int POLICY_EFF_QOS_UI_IS_URGENT ; 
 int POLICY_EFF_ROLE_SHIFT ; 
 int POLICY_EFF_SFI_MANAGED ; 
 int POLICY_EFF_SUP_ACTIVE ; 
 int POLICY_EFF_SUP_CPU ; 
 int POLICY_EFF_TAL_ENGAGED ; 
 int POLICY_EFF_TERMINATED ; 
 int POLICY_EFF_THROUGH_QOS_SHIFT ; 
 int POLICY_EFF_WATCHERS_BG ; 

uint64_t
task_effective_bitfield(task_t task)
{
	uint64_t bits = 0;
	struct task_effective_policy effective = task->effective_policy;

	bits |= (effective.tep_io_tier          ? (((uint64_t)effective.tep_io_tier) << POLICY_EFF_IO_TIER_SHIFT) : 0);
	bits |= (effective.tep_io_passive       ? POLICY_EFF_IO_PASSIVE     : 0);
	bits |= (effective.tep_darwinbg         ? POLICY_EFF_DARWIN_BG      : 0);
	bits |= (effective.tep_lowpri_cpu       ? POLICY_EFF_LOWPRI_CPU     : 0);
	bits |= (effective.tep_terminated       ? POLICY_EFF_TERMINATED     : 0);
	bits |= (effective.tep_all_sockets_bg   ? POLICY_EFF_ALL_SOCKETS_BG : 0);
	bits |= (effective.tep_new_sockets_bg   ? POLICY_EFF_NEW_SOCKETS_BG : 0);
	bits |= (effective.tep_bg_iotier        ? (((uint64_t)effective.tep_bg_iotier) << POLICY_EFF_BG_IOTIER_SHIFT) : 0);
	bits |= (effective.tep_qos_ui_is_urgent ? POLICY_EFF_QOS_UI_IS_URGENT : 0);

	bits |= (effective.tep_tal_engaged      ? POLICY_EFF_TAL_ENGAGED    : 0);
	bits |= (effective.tep_watchers_bg      ? POLICY_EFF_WATCHERS_BG    : 0);
	bits |= (effective.tep_sup_active       ? POLICY_EFF_SUP_ACTIVE     : 0);
	bits |= (effective.tep_suppressed_cpu   ? POLICY_EFF_SUP_CPU        : 0);
	bits |= (effective.tep_role             ? (((uint64_t)effective.tep_role)        << POLICY_EFF_ROLE_SHIFT)        : 0);
	bits |= (effective.tep_latency_qos      ? (((uint64_t)effective.tep_latency_qos) << POLICY_EFF_LATENCY_QOS_SHIFT) : 0);
	bits |= (effective.tep_through_qos      ? (((uint64_t)effective.tep_through_qos) << POLICY_EFF_THROUGH_QOS_SHIFT) : 0);
	bits |= (effective.tep_sfi_managed      ? POLICY_EFF_SFI_MANAGED    : 0);
	bits |= (effective.tep_qos_ceiling      ? (((uint64_t)effective.tep_qos_ceiling) << POLICY_EFF_QOS_CEILING_SHIFT) : 0);

	return bits;
}