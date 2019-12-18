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
struct ip_out_args {int /*<<< orphan*/  ipoa_sotc; int /*<<< orphan*/  ipoa_flags; } ;
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
ipsec_set_ipoa_for_interface(ifnet_t interface, struct ip_out_args *ipoa)
{
	struct ipsec_pcb *pcb;
	
	if (interface == NULL || ipoa == NULL)
		return;
	pcb = ifnet_softc(interface);
	
	if (net_qos_policy_restricted == 0) {
		ipoa->ipoa_flags |= IPOAF_QOSMARKING_ALLOWED;
		ipoa->ipoa_sotc = so_svc2tc(pcb->ipsec_output_service_class);
	} else if (pcb->ipsec_output_service_class != MBUF_SC_VO ||
	   net_qos_policy_restrict_avapps != 0) {
		ipoa->ipoa_flags &= ~IPOAF_QOSMARKING_ALLOWED;
	} else {
		ipoa->ipoa_flags |= IP6OAF_QOSMARKING_ALLOWED;
		ipoa->ipoa_sotc = SO_TC_VO;
	}
}