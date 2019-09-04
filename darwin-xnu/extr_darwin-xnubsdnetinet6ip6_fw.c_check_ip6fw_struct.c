#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int* s6_addr32; } ;
struct TYPE_15__ {int* s6_addr32; } ;
struct TYPE_14__ {int* s6_addr32; } ;
struct TYPE_13__ {int* s6_addr32; } ;
struct TYPE_11__ {int /*<<< orphan*/ * name; } ;
struct TYPE_12__ {TYPE_3__ fu_via_if; } ;
struct TYPE_9__ {int /*<<< orphan*/ * name; } ;
struct TYPE_10__ {TYPE_1__ fu_via_if; } ;
struct ip6_fw {int fw_flg; scalar_t__ fw_prot; scalar_t__ fw_tcpf; scalar_t__ fw_tcpnf; int fw_reject_code; int /*<<< orphan*/  fw_divert_port; scalar_t__ fw_nports; TYPE_8__ fw_dmsk; TYPE_7__ fw_dst; TYPE_6__ fw_smsk; TYPE_5__ fw_src; TYPE_4__ fw_out_if; TYPE_2__ fw_in_if; } ;

/* Variables and functions */
 int IF6_FW_F_VIAHACK ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
#define  IPV6_FW_F_ACCEPT 134 
 int IPV6_FW_F_COMMAND ; 
#define  IPV6_FW_F_COUNT 133 
#define  IPV6_FW_F_DENY 132 
#define  IPV6_FW_F_DIVERT 131 
 int IPV6_FW_F_DRNG ; 
 int IPV6_FW_F_FRAG ; 
 int IPV6_FW_F_IIFNAME ; 
 int IPV6_FW_F_IN ; 
 int IPV6_FW_F_MASK ; 
 int IPV6_FW_F_OIFACE ; 
 int IPV6_FW_F_OIFNAME ; 
 int IPV6_FW_F_OUT ; 
#define  IPV6_FW_F_REJECT 130 
#define  IPV6_FW_F_SKIPTO 129 
 int IPV6_FW_F_SRNG ; 
#define  IPV6_FW_F_TEE 128 
 int IPV6_FW_GETNDSTP (struct ip6_fw*) ; 
 int IPV6_FW_GETNSRCP (struct ip6_fw*) ; 
 int IPV6_FW_MAX_PORTS ; 
 int IPV6_FW_REJECT_RST ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  err_prefix ; 

__attribute__((used)) static struct ip6_fw *
check_ip6fw_struct(struct ip6_fw *frwl)
{
	/* Check for invalid flag bits */
	if ((frwl->fw_flg & ~IPV6_FW_F_MASK) != 0) {
		dprintf(("%s undefined flag bits set (flags=%x)\n",
		    err_prefix, frwl->fw_flg));
		return (NULL);
	}
	/* Must apply to incoming or outgoing (or both) */
	if (!(frwl->fw_flg & (IPV6_FW_F_IN | IPV6_FW_F_OUT))) {
		dprintf(("%s neither in nor out\n", err_prefix));
		return (NULL);
	}
	/* Empty interface name is no good */
	if (((frwl->fw_flg & IPV6_FW_F_IIFNAME)
	      && !*frwl->fw_in_if.fu_via_if.name)
	    || ((frwl->fw_flg & IPV6_FW_F_OIFNAME)
	      && !*frwl->fw_out_if.fu_via_if.name)) {
		dprintf(("%s empty interface name\n", err_prefix));
		return (NULL);
	}
	/* Sanity check interface matching */
	if ((frwl->fw_flg & IF6_FW_F_VIAHACK) == IF6_FW_F_VIAHACK) {
		;		/* allow "via" backwards compatibility */
	} else if ((frwl->fw_flg & IPV6_FW_F_IN)
	    && (frwl->fw_flg & IPV6_FW_F_OIFACE)) {
		dprintf(("%s outgoing interface check on incoming\n",
		    err_prefix));
		return (NULL);
	}
	/* Sanity check port ranges */
	if ((frwl->fw_flg & IPV6_FW_F_SRNG) && IPV6_FW_GETNSRCP(frwl) < 2) {
		dprintf(("%s src range set but n_src_p=%d\n",
		    err_prefix, IPV6_FW_GETNSRCP(frwl)));
		return (NULL);
	}
	if ((frwl->fw_flg & IPV6_FW_F_DRNG) && IPV6_FW_GETNDSTP(frwl) < 2) {
		dprintf(("%s dst range set but n_dst_p=%d\n",
		    err_prefix, IPV6_FW_GETNDSTP(frwl)));
		return (NULL);
	}
	if (IPV6_FW_GETNSRCP(frwl) + IPV6_FW_GETNDSTP(frwl) > IPV6_FW_MAX_PORTS) {
		dprintf(("%s too many ports (%d+%d)\n",
		    err_prefix, IPV6_FW_GETNSRCP(frwl), IPV6_FW_GETNDSTP(frwl)));
		return (NULL);
	}
	/*
	 *	Protocols other than TCP/UDP don't use port range
	 */
	if ((frwl->fw_prot != IPPROTO_TCP) &&
	    (frwl->fw_prot != IPPROTO_UDP) &&
	    (IPV6_FW_GETNSRCP(frwl) || IPV6_FW_GETNDSTP(frwl))) {
		dprintf(("%s port(s) specified for non TCP/UDP rule\n",
		    err_prefix));
		return(NULL);
	}

	/*
	 *	Rather than modify the entry to make such entries work,
	 *	we reject this rule and require user level utilities
	 *	to enforce whatever policy they deem appropriate.
	 */
	if ((frwl->fw_src.s6_addr32[0] & (~frwl->fw_smsk.s6_addr32[0])) ||
		(frwl->fw_src.s6_addr32[1] & (~frwl->fw_smsk.s6_addr32[1])) ||
		(frwl->fw_src.s6_addr32[2] & (~frwl->fw_smsk.s6_addr32[2])) ||
		(frwl->fw_src.s6_addr32[3] & (~frwl->fw_smsk.s6_addr32[3])) ||
		(frwl->fw_dst.s6_addr32[0] & (~frwl->fw_dmsk.s6_addr32[0])) ||
		(frwl->fw_dst.s6_addr32[1] & (~frwl->fw_dmsk.s6_addr32[1])) ||
		(frwl->fw_dst.s6_addr32[2] & (~frwl->fw_dmsk.s6_addr32[2])) ||
		(frwl->fw_dst.s6_addr32[3] & (~frwl->fw_dmsk.s6_addr32[3]))) {
		dprintf(("%s rule never matches\n", err_prefix));
		return(NULL);
	}

	if ((frwl->fw_flg & IPV6_FW_F_FRAG) &&
		(frwl->fw_prot == IPPROTO_UDP || frwl->fw_prot == IPPROTO_TCP)) {
		if (frwl->fw_nports) {
			dprintf(("%s cannot mix 'frag' and ports\n", err_prefix));
			return(NULL);
		}
		if (frwl->fw_prot == IPPROTO_TCP &&
			frwl->fw_tcpf != frwl->fw_tcpnf) {
			dprintf(("%s cannot mix 'frag' with TCP flags\n", err_prefix));
			return(NULL);
		}
	}

	/* Check command specific stuff */
	switch (frwl->fw_flg & IPV6_FW_F_COMMAND)
	{
	case IPV6_FW_F_REJECT:
		if (frwl->fw_reject_code >= 0x100
		    && !(frwl->fw_prot == IPPROTO_TCP
		      && frwl->fw_reject_code == IPV6_FW_REJECT_RST)) {
			dprintf(("%s unknown reject code\n", err_prefix));
			return(NULL);
		}
		break;
	case IPV6_FW_F_DIVERT:		/* Diverting to port zero is invalid */
	case IPV6_FW_F_TEE:
		if (frwl->fw_divert_port == 0) {
			dprintf(("%s can't divert to port 0\n", err_prefix));
			return (NULL);
		}
		break;
	case IPV6_FW_F_DENY:
	case IPV6_FW_F_ACCEPT:
	case IPV6_FW_F_COUNT:
	case IPV6_FW_F_SKIPTO:
		break;
	default:
		dprintf(("%s invalid command\n", err_prefix));
		return(NULL);
	}

	return frwl;
}