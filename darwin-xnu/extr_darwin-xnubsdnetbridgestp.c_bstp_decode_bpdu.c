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
typedef  int uint64_t ;
struct bstp_port {int /*<<< orphan*/  bp_port_id; } ;
struct TYPE_2__ {int pv_root_id; int pv_dbridge_id; int /*<<< orphan*/  pv_port_id; void* pv_dport_id; int /*<<< orphan*/  pv_cost; } ;
struct bstp_config_unit {int cu_topology_change_ack; int cu_proposal; int cu_agree; int cu_learning; int cu_forwarding; int cu_topology_change; void* cu_role; int /*<<< orphan*/  cu_message_type; TYPE_1__ cu_pv; void* cu_forward_delay; void* cu_hello_time; void* cu_max_age; void* cu_message_age; } ;
struct bstp_cbpdu {int cbu_flags; int cbu_protover; int /*<<< orphan*/  cbu_bpdutype; int /*<<< orphan*/  cbu_portid; int /*<<< orphan*/  cbu_forwarddelay; int /*<<< orphan*/  cbu_hellotime; int /*<<< orphan*/  cbu_maxage; int /*<<< orphan*/  cbu_messageage; int /*<<< orphan*/  cbu_rootpathcost; scalar_t__* cbu_bridgeaddr; int /*<<< orphan*/  cbu_bridgepri; scalar_t__* cbu_rootaddr; int /*<<< orphan*/  cbu_rootpri; } ;

/* Variables and functions */
 int BSTP_PDU_F_A ; 
#define  BSTP_PDU_F_ALT 132 
#define  BSTP_PDU_F_DESG 131 
 int BSTP_PDU_F_F ; 
 int BSTP_PDU_F_L ; 
 int BSTP_PDU_F_P ; 
#define  BSTP_PDU_F_ROOT 130 
 int BSTP_PDU_F_TC ; 
 int BSTP_PDU_F_TCA ; 
 int BSTP_PDU_PRMASK ; 
 int BSTP_PDU_PRSHIFT ; 
 int BSTP_PDU_RSTPMASK ; 
 int BSTP_PDU_STPMASK ; 
#define  BSTP_PROTO_RSTP 129 
#define  BSTP_PROTO_STP 128 
 void* BSTP_ROLE_ALTERNATE ; 
 void* BSTP_ROLE_DESIGNATED ; 
 void* BSTP_ROLE_ROOT ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bstp_decode_bpdu(struct bstp_port *bp, struct bstp_cbpdu *cpdu,
    struct bstp_config_unit *cu)
{
	int flags;

	cu->cu_pv.pv_root_id =
	    (((uint64_t)ntohs(cpdu->cbu_rootpri)) << 48) |
	    (((uint64_t)cpdu->cbu_rootaddr[0]) << 40) |
	    (((uint64_t)cpdu->cbu_rootaddr[1]) << 32) |
	    (((uint64_t)cpdu->cbu_rootaddr[2]) << 24) |
	    (((uint64_t)cpdu->cbu_rootaddr[3]) << 16) |
	    (((uint64_t)cpdu->cbu_rootaddr[4]) << 8) |
	    (((uint64_t)cpdu->cbu_rootaddr[5]) << 0);

	cu->cu_pv.pv_dbridge_id =
	    (((uint64_t)ntohs(cpdu->cbu_bridgepri)) << 48) |
	    (((uint64_t)cpdu->cbu_bridgeaddr[0]) << 40) |
	    (((uint64_t)cpdu->cbu_bridgeaddr[1]) << 32) |
	    (((uint64_t)cpdu->cbu_bridgeaddr[2]) << 24) |
	    (((uint64_t)cpdu->cbu_bridgeaddr[3]) << 16) |
	    (((uint64_t)cpdu->cbu_bridgeaddr[4]) << 8) |
	    (((uint64_t)cpdu->cbu_bridgeaddr[5]) << 0);

	cu->cu_pv.pv_cost = ntohl(cpdu->cbu_rootpathcost);
	cu->cu_message_age = ntohs(cpdu->cbu_messageage);
	cu->cu_max_age = ntohs(cpdu->cbu_maxage);
	cu->cu_hello_time = ntohs(cpdu->cbu_hellotime);
	cu->cu_forward_delay = ntohs(cpdu->cbu_forwarddelay);
	cu->cu_pv.pv_dport_id = ntohs(cpdu->cbu_portid);
	cu->cu_pv.pv_port_id = bp->bp_port_id;
	cu->cu_message_type = cpdu->cbu_bpdutype;

	/* Strip off unused flags in STP mode */
	flags = cpdu->cbu_flags;
	switch (cpdu->cbu_protover) {
		case BSTP_PROTO_STP:
			flags &= BSTP_PDU_STPMASK;
			/* A STP BPDU explicitly conveys a Designated Port */
			cu->cu_role = BSTP_ROLE_DESIGNATED;
			break;

		case BSTP_PROTO_RSTP:
			flags &= BSTP_PDU_RSTPMASK;
			break;
	}

	cu->cu_topology_change_ack =
		(flags & BSTP_PDU_F_TCA) ? 1 : 0;
	cu->cu_proposal =
		(flags & BSTP_PDU_F_P) ? 1 : 0;
	cu->cu_agree =
		(flags & BSTP_PDU_F_A) ? 1 : 0;
	cu->cu_learning =
		(flags & BSTP_PDU_F_L) ? 1 : 0;
	cu->cu_forwarding =
		(flags & BSTP_PDU_F_F) ? 1 : 0;
	cu->cu_topology_change =
		(flags & BSTP_PDU_F_TC) ? 1 : 0;

	switch ((flags & BSTP_PDU_PRMASK) >> BSTP_PDU_PRSHIFT) {
		case BSTP_PDU_F_ROOT:
			cu->cu_role = BSTP_ROLE_ROOT;
			break;
		case BSTP_PDU_F_ALT:
			cu->cu_role = BSTP_ROLE_ALTERNATE;
			break;
		case BSTP_PDU_F_DESG:
			cu->cu_role = BSTP_ROLE_DESIGNATED;
			break;
	}
}