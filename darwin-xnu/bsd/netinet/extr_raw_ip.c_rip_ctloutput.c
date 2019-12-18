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
struct sockopt {scalar_t__ sopt_level; scalar_t__ sopt_name; int sopt_dir; } ;
struct socket {int dummy; } ;
struct inpcb {int inp_flags; } ;
typedef  int /*<<< orphan*/  optval ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMYNET_LOADED ; 
 int EINVAL ; 
 int ENOPROTOOPT ; 
 int INP_HDRINCL ; 
 int INP_STRIPHDR ; 
 scalar_t__ IPPROTO_IP ; 
#define  IP_DUMMYNET_CONFIGURE 148 
#define  IP_DUMMYNET_DEL 147 
#define  IP_DUMMYNET_FLUSH 146 
#define  IP_DUMMYNET_GET 145 
#define  IP_FW_ADD 144 
#define  IP_FW_DEL 143 
#define  IP_FW_FLUSH 142 
#define  IP_FW_GET 141 
#define  IP_FW_RESETLOG 140 
#define  IP_FW_ZERO 139 
#define  IP_HDRINCL 138 
#define  IP_OLD_FW_ADD 137 
#define  IP_OLD_FW_DEL 136 
#define  IP_OLD_FW_FLUSH 135 
#define  IP_OLD_FW_GET 134 
#define  IP_OLD_FW_RESETLOG 133 
#define  IP_OLD_FW_ZERO 132 
#define  IP_STRIPHDR 131 
 scalar_t__ SOL_SOCKET ; 
#define  SOPT_GET 130 
#define  SOPT_SET 129 
#define  SO_FLUSH 128 
 int inp_flush (struct inpcb*,int) ; 
 int ip_ctloutput (struct socket*,struct sockopt*) ; 
 int ip_dn_ctl_ptr (struct sockopt*) ; 
 int /*<<< orphan*/  ip_dn_init () ; 
 int ip_fw_ctl_ptr (struct sockopt*) ; 
 int load_ipfw () ; 
 int sooptcopyin (struct sockopt*,int*,int,int) ; 
 int sooptcopyout (struct sockopt*,int*,int) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

int
rip_ctloutput(struct socket *so, struct sockopt *sopt)
{
	struct	inpcb *inp = sotoinpcb(so);
	int	error, optval;

	/* Allow <SOL_SOCKET,SO_FLUSH> at this level */
	if (sopt->sopt_level != IPPROTO_IP &&
	    !(sopt->sopt_level == SOL_SOCKET && sopt->sopt_name == SO_FLUSH))
		return (EINVAL);

	error = 0;

	switch (sopt->sopt_dir) {
	case SOPT_GET:
		switch (sopt->sopt_name) {
		case IP_HDRINCL:
			optval = inp->inp_flags & INP_HDRINCL;
			error = sooptcopyout(sopt, &optval, sizeof optval);
			break;

		case IP_STRIPHDR:
			optval = inp->inp_flags & INP_STRIPHDR;
			error = sooptcopyout(sopt, &optval, sizeof optval);
			break;

#if IPFIREWALL
		case IP_FW_ADD:
		case IP_FW_GET:
		case IP_OLD_FW_ADD:
		case IP_OLD_FW_GET:
			if (ip_fw_ctl_ptr == 0)
				error = load_ipfw();
			if (ip_fw_ctl_ptr && error == 0)
				error = ip_fw_ctl_ptr(sopt);
			else
				error = ENOPROTOOPT;
			break;
#endif /* IPFIREWALL */

#if DUMMYNET
		case IP_DUMMYNET_GET:
			if (!DUMMYNET_LOADED)
				ip_dn_init();
			if (DUMMYNET_LOADED)
				error = ip_dn_ctl_ptr(sopt);
			else
				error = ENOPROTOOPT;
			break ;
#endif /* DUMMYNET */

		default:
			error = ip_ctloutput(so, sopt);
			break;
		}
		break;

	case SOPT_SET:
		switch (sopt->sopt_name) {
		case IP_HDRINCL:
			error = sooptcopyin(sopt, &optval, sizeof optval,
					    sizeof optval);
			if (error)
				break;
			if (optval)
				inp->inp_flags |= INP_HDRINCL;
			else
				inp->inp_flags &= ~INP_HDRINCL;
			break;

		case IP_STRIPHDR:
			error = sooptcopyin(sopt, &optval, sizeof optval,
			    sizeof optval);
			if (error)
				break;
			if (optval)
				inp->inp_flags |= INP_STRIPHDR;
			else
				inp->inp_flags &= ~INP_STRIPHDR;
			break;

#if IPFIREWALL
		case IP_FW_ADD:
		case IP_FW_DEL:
		case IP_FW_FLUSH:
		case IP_FW_ZERO:
		case IP_FW_RESETLOG:
		case IP_OLD_FW_ADD:
		case IP_OLD_FW_DEL:
		case IP_OLD_FW_FLUSH:
		case IP_OLD_FW_ZERO:
		case IP_OLD_FW_RESETLOG:
			if (ip_fw_ctl_ptr == 0)
				error = load_ipfw();
			if (ip_fw_ctl_ptr && error == 0)
				error = ip_fw_ctl_ptr(sopt);
			else
				error = ENOPROTOOPT;
			break;
#endif /* IPFIREWALL */

#if DUMMYNET
		case IP_DUMMYNET_CONFIGURE:
		case IP_DUMMYNET_DEL:
		case IP_DUMMYNET_FLUSH:
			if (!DUMMYNET_LOADED)
				ip_dn_init();
			if (DUMMYNET_LOADED)
				error = ip_dn_ctl_ptr(sopt);
			else
				error = ENOPROTOOPT ;
			break ;
#endif

		case SO_FLUSH:
			if ((error = sooptcopyin(sopt, &optval, sizeof (optval),
			    sizeof (optval))) != 0)
				break;

			error = inp_flush(inp, optval);
			break;

		default:
			error = ip_ctloutput(so, sopt);
			break;
		}
		break;
	}

	return (error);
}