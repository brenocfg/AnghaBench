#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ether_header {int dummy; } ;
typedef  TYPE_2__* mbuf_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  (* bpf_packet_func ) (int /*<<< orphan*/ ,TYPE_2__*) ;
struct TYPE_9__ {int csum_flags; int /*<<< orphan*/  vlan_tag; } ;
struct TYPE_10__ {int /*<<< orphan*/  m_len; int /*<<< orphan*/  m_data; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int CSUM_VLAN_TAG_VALID ; 
 scalar_t__ ETHER_HDR_LEN ; 
 int /*<<< orphan*/  bond_bpf_vlan (int /*<<< orphan*/ ,TYPE_2__*,struct ether_header const*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,TYPE_2__*)) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static __inline__ void 
bond_bpf_input(ifnet_t ifp, mbuf_t m, const struct ether_header * eh_p,
		bpf_packet_func func)
{
    if (func != NULL) {
	if (m->m_pkthdr.csum_flags & CSUM_VLAN_TAG_VALID) {
	    bond_bpf_vlan(ifp, m, eh_p, m->m_pkthdr.vlan_tag, func);
	} else {
	    /* restore the header */
	    m->m_data -= ETHER_HDR_LEN;
	    m->m_len += ETHER_HDR_LEN;
	    (*func)(ifp, m);
	    m->m_data += ETHER_HDR_LEN;
	    m->m_len -= ETHER_HDR_LEN;
	}
    }
    return;
}