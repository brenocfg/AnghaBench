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
struct TYPE_16__ {int s_addr; } ;
struct TYPE_15__ {int s_addr; } ;
struct TYPE_14__ {int s_addr; } ;
struct TYPE_13__ {int s_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/ * name; } ;
struct TYPE_12__ {TYPE_3__ fu_via_if_compat; } ;
struct TYPE_9__ {int /*<<< orphan*/ * name; } ;
struct TYPE_10__ {TYPE_1__ fu_via_if_compat; } ;
struct ip_fw_compat_64 {int fw_flg; scalar_t__ fw_prot; scalar_t__ fw_tcpf; scalar_t__ fw_tcpnf; int fw_reject_code_compat; int /*<<< orphan*/  fw_divert_port_compat; scalar_t__ fw_nports; TYPE_8__ fw_dmsk; TYPE_7__ fw_dst; TYPE_6__ fw_smsk; TYPE_5__ fw_src; TYPE_4__ fw_out_if; TYPE_2__ fw_in_if; } ;

/* Variables and functions */
 int EINVAL ; 
 int IF_FW_F_VIAHACK_COMPAT ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
#define  IP_FW_F_ACCEPT_COMPAT 138 
 int IP_FW_F_CHECK_S_COMPAT ; 
 int IP_FW_F_COMMAND_COMPAT ; 
#define  IP_FW_F_COUNT_COMPAT 137 
#define  IP_FW_F_DENY_COMPAT 136 
#define  IP_FW_F_DIVERT_COMPAT 135 
 int IP_FW_F_DRNG_COMPAT ; 
 int IP_FW_F_FRAG_COMPAT ; 
#define  IP_FW_F_FWD_COMPAT 134 
 int IP_FW_F_IIFNAME_COMPAT ; 
 int IP_FW_F_IN_COMPAT ; 
 int IP_FW_F_MASK_COMPAT ; 
 int IP_FW_F_OIFACE_COMPAT ; 
 int IP_FW_F_OIFNAME_COMPAT ; 
 int IP_FW_F_OUT_COMPAT ; 
#define  IP_FW_F_PIPE_COMPAT 133 
#define  IP_FW_F_QUEUE_COMPAT 132 
#define  IP_FW_F_REJECT_COMPAT 131 
#define  IP_FW_F_SKIPTO_COMPAT 130 
 int IP_FW_F_SRNG_COMPAT ; 
#define  IP_FW_F_TEE_COMPAT 129 
#define  IP_FW_F_UID_COMPAT 128 
 int IP_FW_GETNDSTP_COMPAT (struct ip_fw_compat_64*) ; 
 int IP_FW_GETNSRCP_COMPAT (struct ip_fw_compat_64*) ; 
 int IP_FW_MAX_PORTS_COMPAT ; 
 int IP_FW_REJECT_RST_COMPAT ; 

__attribute__((used)) static int
ipfw_check_vers1_struct_64(struct ip_fw_compat_64 *frwl)
{
	/* Check for invalid flag bits */
	if ((frwl->fw_flg & ~IP_FW_F_MASK_COMPAT) != 0) {
		/* 
		printf(("%s undefined flag bits set (flags=%x)\n",
		    err_prefix, frwl->fw_flg));
		*/
		 
		return (EINVAL);
	}
	if (frwl->fw_flg == IP_FW_F_CHECK_S_COMPAT) {
		/* check-state */
		return 0 ;
	}
	/* Must apply to incoming or outgoing (or both) */
	if (!(frwl->fw_flg & (IP_FW_F_IN_COMPAT | IP_FW_F_OUT_COMPAT))) {
		/*
		printf(("%s neither in nor out\n", err_prefix));
		*/
		
		return (EINVAL);
	}
	/* Empty interface name is no good */
	if (((frwl->fw_flg & IP_FW_F_IIFNAME_COMPAT)
	      && !*frwl->fw_in_if.fu_via_if_compat.name)
	    || ((frwl->fw_flg & IP_FW_F_OIFNAME_COMPAT)
	      && !*frwl->fw_out_if.fu_via_if_compat.name)) {
		/*
		printf(("%s empty interface name\n", err_prefix));
		*/
		
		return (EINVAL);
	}
	/* Sanity check interface matching */
	if ((frwl->fw_flg & IF_FW_F_VIAHACK_COMPAT) == IF_FW_F_VIAHACK_COMPAT) {
		;		/* allow "via" backwards compatibility */
	} else if ((frwl->fw_flg & IP_FW_F_IN_COMPAT)
	    && (frwl->fw_flg & IP_FW_F_OIFACE_COMPAT)) {
		/*
		printf(("%s outgoing interface check on incoming\n",
		    err_prefix));
		*/
		
		return (EINVAL);
	}
	/* Sanity check port ranges */
	if ((frwl->fw_flg & IP_FW_F_SRNG_COMPAT) && IP_FW_GETNSRCP_COMPAT(frwl) < 2) {
		/*
		printf(("%s src range set but n_src_p=%d\n",
		    err_prefix, IP_FW_GETNSRCP_COMPAT(frwl)));
		*/
		
		return (EINVAL);
	}
	if ((frwl->fw_flg & IP_FW_F_DRNG_COMPAT) && IP_FW_GETNDSTP_COMPAT(frwl) < 2) {
		/*
		printf(("%s dst range set but n_dst_p=%d\n",
		    err_prefix, IP_FW_GETNDSTP_COMPAT(frwl)));
		*/

		return (EINVAL);
	}
	if (IP_FW_GETNSRCP_COMPAT(frwl) + IP_FW_GETNDSTP_COMPAT(frwl) > IP_FW_MAX_PORTS_COMPAT) {
		/*
		printf(("%s too many ports (%d+%d)\n",
		    err_prefix, IP_FW_GETNSRCP_COMPAT(frwl), IP_FW_GETNDSTP_COMPAT(frwl)));
		*/
		
		return (EINVAL);
	}
	/*
	 *	Protocols other than TCP/UDP don't use port range
	 */
	if ((frwl->fw_prot != IPPROTO_TCP) &&
	    (frwl->fw_prot != IPPROTO_UDP) &&
	    (IP_FW_GETNSRCP_COMPAT(frwl) || IP_FW_GETNDSTP_COMPAT(frwl))) {
		/*
		printf(("%s port(s) specified for non TCP/UDP rule\n",
		    err_prefix));
		*/
		
		return (EINVAL);
	}

	/*
	 *	Rather than modify the entry to make such entries work, 
	 *	we reject this rule and require user level utilities
	 *	to enforce whatever policy they deem appropriate.
	 */
	if ((frwl->fw_src.s_addr & (~frwl->fw_smsk.s_addr)) || 
		(frwl->fw_dst.s_addr & (~frwl->fw_dmsk.s_addr))) {
		/*
		printf(("%s rule never matches\n", err_prefix));
		*/
		
		return (EINVAL);
	}

	if ((frwl->fw_flg & IP_FW_F_FRAG_COMPAT) &&
		(frwl->fw_prot == IPPROTO_UDP || frwl->fw_prot == IPPROTO_TCP)) {
		if (frwl->fw_nports) {
		/*
			printf(("%s cannot mix 'frag' and ports\n", err_prefix));
		*/
		
			return (EINVAL);
		}
		if (frwl->fw_prot == IPPROTO_TCP &&
			frwl->fw_tcpf != frwl->fw_tcpnf) {
		/*
			printf(("%s cannot mix 'frag' and TCP flags\n", err_prefix));
		*/
		
			return (EINVAL);
		}
	}

	/* Check command specific stuff */
	switch (frwl->fw_flg & IP_FW_F_COMMAND_COMPAT)
	{
	case IP_FW_F_REJECT_COMPAT:
		if (frwl->fw_reject_code_compat >= 0x100
		    && !(frwl->fw_prot == IPPROTO_TCP
		      && frwl->fw_reject_code_compat == IP_FW_REJECT_RST_COMPAT)) {
		/*
			printf(("%s unknown reject code\n", err_prefix));
		*/
		
			return (EINVAL);
		}
		break;
	case IP_FW_F_DIVERT_COMPAT:		/* Diverting to port zero is invalid */
	case IP_FW_F_TEE_COMPAT:
	case IP_FW_F_PIPE_COMPAT:              /* piping through 0 is invalid */
	case IP_FW_F_QUEUE_COMPAT:             /* piping through 0 is invalid */
		if (frwl->fw_divert_port_compat == 0) {
		/*
			printf(("%s can't divert to port 0\n", err_prefix));
		*/
		
			return (EINVAL);
		}
		break;
	case IP_FW_F_DENY_COMPAT:
	case IP_FW_F_ACCEPT_COMPAT:
	case IP_FW_F_COUNT_COMPAT:
	case IP_FW_F_SKIPTO_COMPAT:
	case IP_FW_F_FWD_COMPAT:
	case IP_FW_F_UID_COMPAT:
		break;
	default:
		/*
		printf(("%s invalid command\n", err_prefix));
		*/
		
		return (EINVAL);
	}

	return 0;
}