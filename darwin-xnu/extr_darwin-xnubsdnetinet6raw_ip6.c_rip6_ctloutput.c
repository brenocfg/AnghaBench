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
typedef  int /*<<< orphan*/  optval ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 scalar_t__ IPPROTO_IPV6 ; 
#define  IPV6_CHECKSUM 131 
 scalar_t__ SOL_SOCKET ; 
#define  SOPT_GET 130 
#define  SOPT_SET 129 
#define  SO_FLUSH 128 
 int icmp6_ctloutput (struct socket*,struct sockopt*) ; 
 int inp_flush (int /*<<< orphan*/ ,int) ; 
 int ip6_ctloutput (struct socket*,struct sockopt*) ; 
 int ip6_raw_ctloutput (struct socket*,struct sockopt*) ; 
 int sooptcopyin (struct sockopt*,int*,int,int) ; 
 int /*<<< orphan*/  sotoinpcb (struct socket*) ; 

int
rip6_ctloutput(
	struct socket *so,
	struct sockopt *sopt)
{
	int error, optval;

	/* Allow <SOL_SOCKET,SO_FLUSH> at this level */
	if (sopt->sopt_level == IPPROTO_ICMPV6)
		/*
		 * XXX: is it better to call icmp6_ctloutput() directly
		 * from protosw?
		 */
		return(icmp6_ctloutput(so, sopt));
	else if (sopt->sopt_level != IPPROTO_IPV6 &&
	    !(sopt->sopt_level == SOL_SOCKET && sopt->sopt_name == SO_FLUSH))
		return (EINVAL);

	error = 0;

	switch (sopt->sopt_dir) {
	case SOPT_GET:
		switch (sopt->sopt_name) {
		case IPV6_CHECKSUM:
			error = ip6_raw_ctloutput(so, sopt);
			break;
		default:
			error = ip6_ctloutput(so, sopt);
			break;
		}
		break;

	case SOPT_SET:
		switch (sopt->sopt_name) {
		case IPV6_CHECKSUM:
			error = ip6_raw_ctloutput(so, sopt);
			break;

		case SO_FLUSH:
			if ((error = sooptcopyin(sopt, &optval, sizeof (optval),
			    sizeof (optval))) != 0)
				break;

			error = inp_flush(sotoinpcb(so), optval);
			break;

		default:
			error = ip6_ctloutput(so, sopt);
			break;
		}
		break;
	}

	return (error);
}