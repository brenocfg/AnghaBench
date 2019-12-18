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
struct ipsec_pcb {scalar_t__ ipsec_output_service_class; } ;
struct ip6_out_args {int /*<<< orphan*/  ip6oa_sotc; int /*<<< orphan*/  ip6oa_flags; } ;
typedef  int /*<<< orphan*/ * ifnet_t ;

/* Variables and functions */
 int /*<<< orphan*/  IP6OAF_QOSMARKING_ALLOWED ; 
 int /*<<< orphan*/  IPOAF_QOSMARKING_ALLOWED ; 
 scalar_t__ MBUF_SC_VO ; 
 int /*<<< orphan*/  SO_TC_VO ; 
 struct ipsec_pcb* ifnet_softc (int /*<<< orphan*/ *) ; 
 scalar_t__ net_qos_policy_restrict_avapps ; 
 scalar_t__ net_qos_policy_restricted ; 
 int /*<<< orphan*/  so_svc2tc (scalar_t__) ; 

void
ipsec_set_ip6oa_for_interface(ifnet_t interface, struct ip6_out_args *ip6oa)
{
	struct ipsec_pcb *pcb;
	
	if (interface == NULL || ip6oa == NULL)
		return;
	pcb = ifnet_softc(interface);
	
	if (net_qos_policy_restricted == 0) {
		ip6oa->ip6oa_flags |= IPOAF_QOSMARKING_ALLOWED;
		ip6oa->ip6oa_sotc = so_svc2tc(pcb->ipsec_output_service_class);
	} else if (pcb->ipsec_output_service_class != MBUF_SC_VO ||
	   net_qos_policy_restrict_avapps != 0) {
		ip6oa->ip6oa_flags &= ~IPOAF_QOSMARKING_ALLOWED;
	} else {
		ip6oa->ip6oa_flags |= IP6OAF_QOSMARKING_ALLOWED;
		ip6oa->ip6oa_sotc = SO_TC_VO;
	}
}