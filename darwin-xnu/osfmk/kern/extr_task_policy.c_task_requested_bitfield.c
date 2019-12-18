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
struct task_requested_policy {scalar_t__ trp_qos_clamp; scalar_t__ trp_sfi_managed; scalar_t__ trp_over_through_qos; scalar_t__ trp_base_through_qos; scalar_t__ trp_over_latency_qos; scalar_t__ trp_base_latency_qos; scalar_t__ trp_sup_bg_sockets; scalar_t__ trp_sup_disk; scalar_t__ trp_sup_throughput; scalar_t__ trp_sup_timer; scalar_t__ trp_sup_cpu; scalar_t__ trp_sup_lowpri_cpu; scalar_t__ trp_sup_active; scalar_t__ trp_role; scalar_t__ trp_apptype; scalar_t__ trp_tal_enabled; scalar_t__ trp_boosted; scalar_t__ trp_terminated; scalar_t__ trp_bg_iotier; scalar_t__ trp_ext_iopassive; scalar_t__ trp_int_iopassive; scalar_t__ trp_ext_iotier; scalar_t__ trp_int_iotier; scalar_t__ trp_ext_darwinbg; scalar_t__ trp_int_darwinbg; } ;
struct TYPE_3__ {struct task_requested_policy requested_policy; } ;

/* Variables and functions */
 int POLICY_REQ_APPTYPE_SHIFT ; 
 int POLICY_REQ_BASE_LATENCY_QOS_SHIFT ; 
 int POLICY_REQ_BASE_THROUGH_QOS_SHIFT ; 
 int POLICY_REQ_BG_IOTIER_SHIFT ; 
 int POLICY_REQ_BOOSTED ; 
 int POLICY_REQ_EXT_DARWIN_BG ; 
 int POLICY_REQ_EXT_IO_TIER_SHIFT ; 
 int POLICY_REQ_EXT_PASSIVE_IO ; 
 int POLICY_REQ_INT_DARWIN_BG ; 
 int POLICY_REQ_INT_IO_TIER_SHIFT ; 
 int POLICY_REQ_INT_PASSIVE_IO ; 
 int POLICY_REQ_OVER_LATENCY_QOS_SHIFT ; 
 int POLICY_REQ_OVER_THROUGH_QOS_SHIFT ; 
 int POLICY_REQ_QOS_CLAMP_SHIFT ; 
 int POLICY_REQ_ROLE_SHIFT ; 
 int POLICY_REQ_SFI_MANAGED ; 
 int POLICY_REQ_SUP_ACTIVE ; 
 int POLICY_REQ_SUP_BG_SOCKETS ; 
 int POLICY_REQ_SUP_CPU ; 
 int POLICY_REQ_SUP_DISK_THROTTLE ; 
 int POLICY_REQ_SUP_LOWPRI_CPU ; 
 int POLICY_REQ_SUP_THROUGHPUT_SHIFT ; 
 int POLICY_REQ_SUP_TIMER_THROTTLE_SHIFT ; 
 int POLICY_REQ_TAL_ENABLED ; 
 int POLICY_REQ_TERMINATED ; 

uint64_t
task_requested_bitfield(task_t task)
{
	uint64_t bits = 0;
	struct task_requested_policy requested = task->requested_policy;

	bits |= (requested.trp_int_darwinbg     ? POLICY_REQ_INT_DARWIN_BG  : 0);
	bits |= (requested.trp_ext_darwinbg     ? POLICY_REQ_EXT_DARWIN_BG  : 0);
	bits |= (requested.trp_int_iotier       ? (((uint64_t)requested.trp_int_iotier) << POLICY_REQ_INT_IO_TIER_SHIFT) : 0);
	bits |= (requested.trp_ext_iotier       ? (((uint64_t)requested.trp_ext_iotier) << POLICY_REQ_EXT_IO_TIER_SHIFT) : 0);
	bits |= (requested.trp_int_iopassive    ? POLICY_REQ_INT_PASSIVE_IO : 0);
	bits |= (requested.trp_ext_iopassive    ? POLICY_REQ_EXT_PASSIVE_IO : 0);
	bits |= (requested.trp_bg_iotier        ? (((uint64_t)requested.trp_bg_iotier)  << POLICY_REQ_BG_IOTIER_SHIFT)   : 0);
	bits |= (requested.trp_terminated       ? POLICY_REQ_TERMINATED     : 0);

	bits |= (requested.trp_boosted          ? POLICY_REQ_BOOSTED        : 0);
	bits |= (requested.trp_tal_enabled      ? POLICY_REQ_TAL_ENABLED    : 0);
	bits |= (requested.trp_apptype          ? (((uint64_t)requested.trp_apptype) << POLICY_REQ_APPTYPE_SHIFT)  : 0);
	bits |= (requested.trp_role             ? (((uint64_t)requested.trp_role)    << POLICY_REQ_ROLE_SHIFT)     : 0);

	bits |= (requested.trp_sup_active       ? POLICY_REQ_SUP_ACTIVE         : 0);
	bits |= (requested.trp_sup_lowpri_cpu   ? POLICY_REQ_SUP_LOWPRI_CPU     : 0);
	bits |= (requested.trp_sup_cpu          ? POLICY_REQ_SUP_CPU            : 0);
	bits |= (requested.trp_sup_timer        ? (((uint64_t)requested.trp_sup_timer)        << POLICY_REQ_SUP_TIMER_THROTTLE_SHIFT) : 0);
	bits |= (requested.trp_sup_throughput   ? (((uint64_t)requested.trp_sup_throughput)   << POLICY_REQ_SUP_THROUGHPUT_SHIFT)     : 0);
	bits |= (requested.trp_sup_disk         ? POLICY_REQ_SUP_DISK_THROTTLE  : 0);
	bits |= (requested.trp_sup_bg_sockets   ? POLICY_REQ_SUP_BG_SOCKETS     : 0);

	bits |= (requested.trp_base_latency_qos ? (((uint64_t)requested.trp_base_latency_qos) << POLICY_REQ_BASE_LATENCY_QOS_SHIFT) : 0);
	bits |= (requested.trp_over_latency_qos ? (((uint64_t)requested.trp_over_latency_qos) << POLICY_REQ_OVER_LATENCY_QOS_SHIFT) : 0);
	bits |= (requested.trp_base_through_qos ? (((uint64_t)requested.trp_base_through_qos) << POLICY_REQ_BASE_THROUGH_QOS_SHIFT) : 0);
	bits |= (requested.trp_over_through_qos ? (((uint64_t)requested.trp_over_through_qos) << POLICY_REQ_OVER_THROUGH_QOS_SHIFT) : 0);
	bits |= (requested.trp_sfi_managed      ? POLICY_REQ_SFI_MANAGED        : 0);
	bits |= (requested.trp_qos_clamp        ? (((uint64_t)requested.trp_qos_clamp)        << POLICY_REQ_QOS_CLAMP_SHIFT)        : 0);

	return bits;
}