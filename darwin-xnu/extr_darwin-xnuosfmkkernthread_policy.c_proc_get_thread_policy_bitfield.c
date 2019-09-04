#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* thread_policy_state_t ;
struct thread_requested_policy {scalar_t__ thrp_through_qos; scalar_t__ thrp_latency_qos; scalar_t__ thrp_pidbind_bg; scalar_t__ thrp_qos_override; scalar_t__ thrp_qos; scalar_t__ thrp_ext_iopassive; scalar_t__ thrp_int_iopassive; scalar_t__ thrp_ext_iotier; scalar_t__ thrp_int_iotier; scalar_t__ thrp_ext_darwinbg; scalar_t__ thrp_int_darwinbg; } ;
struct thread_effective_policy {scalar_t__ thep_through_qos; scalar_t__ thep_latency_qos; scalar_t__ thep_qos; scalar_t__ thep_new_sockets_bg; scalar_t__ thep_all_sockets_bg; scalar_t__ thep_io_passive; scalar_t__ thep_io_tier; scalar_t__ thep_darwinbg; } ;
typedef  void* integer_t ;
struct TYPE_6__ {scalar_t__ pending; void* effective; void* requested; } ;
struct TYPE_5__ {struct thread_effective_policy effective_policy; struct thread_requested_policy requested_policy; } ;

/* Variables and functions */
 int POLICY_EFF_ALL_SOCKETS_BG ; 
 int POLICY_EFF_DARWIN_BG ; 
 int POLICY_EFF_IO_PASSIVE ; 
 int POLICY_EFF_IO_TIER_SHIFT ; 
 int POLICY_EFF_LATENCY_QOS_SHIFT ; 
 int POLICY_EFF_NEW_SOCKETS_BG ; 
 int POLICY_EFF_THROUGH_QOS_SHIFT ; 
 int POLICY_EFF_TH_QOS_SHIFT ; 
 int POLICY_REQ_BASE_LATENCY_QOS_SHIFT ; 
 int POLICY_REQ_BASE_THROUGH_QOS_SHIFT ; 
 int POLICY_REQ_EXT_DARWIN_BG ; 
 int POLICY_REQ_EXT_IO_TIER_SHIFT ; 
 int POLICY_REQ_EXT_PASSIVE_IO ; 
 int POLICY_REQ_INT_DARWIN_BG ; 
 int POLICY_REQ_INT_IO_TIER_SHIFT ; 
 int POLICY_REQ_INT_PASSIVE_IO ; 
 int POLICY_REQ_PIDBIND_BG ; 
 int POLICY_REQ_TH_QOS_OVER_SHIFT ; 
 int POLICY_REQ_TH_QOS_SHIFT ; 

__attribute__((used)) static void
proc_get_thread_policy_bitfield(thread_t thread, thread_policy_state_t info)
{
	uint64_t bits = 0;
	struct thread_requested_policy requested = thread->requested_policy;

	bits |= (requested.thrp_int_darwinbg    ? POLICY_REQ_INT_DARWIN_BG  : 0);
	bits |= (requested.thrp_ext_darwinbg    ? POLICY_REQ_EXT_DARWIN_BG  : 0);
	bits |= (requested.thrp_int_iotier      ? (((uint64_t)requested.thrp_int_iotier) << POLICY_REQ_INT_IO_TIER_SHIFT) : 0);
	bits |= (requested.thrp_ext_iotier      ? (((uint64_t)requested.thrp_ext_iotier) << POLICY_REQ_EXT_IO_TIER_SHIFT) : 0);
	bits |= (requested.thrp_int_iopassive   ? POLICY_REQ_INT_PASSIVE_IO : 0);
	bits |= (requested.thrp_ext_iopassive   ? POLICY_REQ_EXT_PASSIVE_IO : 0);

	bits |= (requested.thrp_qos             ? (((uint64_t)requested.thrp_qos) << POLICY_REQ_TH_QOS_SHIFT) : 0);
	bits |= (requested.thrp_qos_override    ? (((uint64_t)requested.thrp_qos_override) << POLICY_REQ_TH_QOS_OVER_SHIFT)   : 0);

	bits |= (requested.thrp_pidbind_bg      ? POLICY_REQ_PIDBIND_BG     : 0);

	bits |= (requested.thrp_latency_qos     ? (((uint64_t)requested.thrp_latency_qos) << POLICY_REQ_BASE_LATENCY_QOS_SHIFT) : 0);
	bits |= (requested.thrp_through_qos     ? (((uint64_t)requested.thrp_through_qos) << POLICY_REQ_BASE_THROUGH_QOS_SHIFT) : 0);

	info->requested = (integer_t) bits;
	bits = 0;

	struct thread_effective_policy effective = thread->effective_policy;

	bits |= (effective.thep_darwinbg        ? POLICY_EFF_DARWIN_BG      : 0);

	bits |= (effective.thep_io_tier         ? (((uint64_t)effective.thep_io_tier) << POLICY_EFF_IO_TIER_SHIFT) : 0);
	bits |= (effective.thep_io_passive      ? POLICY_EFF_IO_PASSIVE     : 0);
	bits |= (effective.thep_all_sockets_bg  ? POLICY_EFF_ALL_SOCKETS_BG : 0);
	bits |= (effective.thep_new_sockets_bg  ? POLICY_EFF_NEW_SOCKETS_BG : 0);

	bits |= (effective.thep_qos             ? (((uint64_t)effective.thep_qos) << POLICY_EFF_TH_QOS_SHIFT) : 0);

	bits |= (effective.thep_latency_qos     ? (((uint64_t)effective.thep_latency_qos) << POLICY_EFF_LATENCY_QOS_SHIFT) : 0);
	bits |= (effective.thep_through_qos     ? (((uint64_t)effective.thep_through_qos) << POLICY_EFF_THROUGH_QOS_SHIFT) : 0);

	info->effective = (integer_t)bits;
	bits = 0;

	info->pending = 0;
}