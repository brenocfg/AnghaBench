#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct sockaddr_ib {void* sib_sid_mask; void* sib_sid; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {scalar_t__ ps; } ;
struct rdma_id_private {TYPE_1__ id; } ;
struct idr {int dummy; } ;

/* Variables and functions */
 int RDMA_IB_IP_PS_IB ; 
 int RDMA_IB_IP_PS_MASK ; 
 int RDMA_IB_IP_PS_TCP ; 
 int RDMA_IB_IP_PS_UDP ; 
 scalar_t__ RDMA_PS_IB ; 
 scalar_t__ RDMA_PS_TCP ; 
 scalar_t__ RDMA_PS_UDP ; 
 int be64_to_cpu (void*) ; 
 int /*<<< orphan*/  cma_port (struct sockaddr*) ; 
 scalar_t__ cma_src_addr (struct rdma_id_private*) ; 
 void* cpu_to_be64 (int) ; 
 struct idr ib_ps ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct idr tcp_ps ; 
 struct idr udp_ps ; 

__attribute__((used)) static struct idr *cma_select_ib_ps(struct rdma_id_private *id_priv)
{
	struct idr *ps = NULL;
	struct sockaddr_ib *sib;
	u64 sid_ps, mask, sid;

	sib = (struct sockaddr_ib *) cma_src_addr(id_priv);
	mask = be64_to_cpu(sib->sib_sid_mask) & RDMA_IB_IP_PS_MASK;
	sid = be64_to_cpu(sib->sib_sid) & mask;

	if ((id_priv->id.ps == RDMA_PS_IB) && (sid == (RDMA_IB_IP_PS_IB & mask))) {
		sid_ps = RDMA_IB_IP_PS_IB;
		ps = &ib_ps;
	} else if (((id_priv->id.ps == RDMA_PS_IB) || (id_priv->id.ps == RDMA_PS_TCP)) &&
		   (sid == (RDMA_IB_IP_PS_TCP & mask))) {
		sid_ps = RDMA_IB_IP_PS_TCP;
		ps = &tcp_ps;
	} else if (((id_priv->id.ps == RDMA_PS_IB) || (id_priv->id.ps == RDMA_PS_UDP)) &&
		   (sid == (RDMA_IB_IP_PS_UDP & mask))) {
		sid_ps = RDMA_IB_IP_PS_UDP;
		ps = &udp_ps;
	}

	if (ps) {
		sib->sib_sid = cpu_to_be64(sid_ps | ntohs(cma_port((struct sockaddr *) sib)));
		sib->sib_sid_mask = cpu_to_be64(RDMA_IB_IP_PS_MASK |
						be64_to_cpu(sib->sib_sid_mask));
	}
	return ps;
}