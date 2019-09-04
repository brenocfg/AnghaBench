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
struct sockopt {scalar_t__ sopt_level; int sopt_name; } ;
struct socket {int /*<<< orphan*/  so_cred; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
#define  ICMP6_FILTER 157 
 scalar_t__ IPPROTO_ICMPV6 ; 
 scalar_t__ IPPROTO_IPV6 ; 
#define  IPV6_2292DSTOPTS 156 
#define  IPV6_2292HOPLIMIT 155 
#define  IPV6_2292HOPOPTS 154 
#define  IPV6_2292PKTINFO 153 
#define  IPV6_2292PKTOPTIONS 152 
#define  IPV6_2292RTHDR 151 
#define  IPV6_BOUND_IF 150 
#define  IPV6_CHECKSUM 149 
#define  IPV6_DSTOPTS 148 
#define  IPV6_HOPLIMIT 147 
#define  IPV6_HOPOPTS 146 
#define  IPV6_IPSEC_POLICY 145 
#define  IPV6_JOIN_GROUP 144 
#define  IPV6_LEAVE_GROUP 143 
#define  IPV6_MULTICAST_HOPS 142 
#define  IPV6_MULTICAST_IF 141 
#define  IPV6_MULTICAST_LOOP 140 
#define  IPV6_NO_IFT_CELLULAR 139 
#define  IPV6_PATHMTU 138 
#define  IPV6_PKTINFO 137 
#define  IPV6_PORTRANGE 136 
#define  IPV6_RECVHOPLIMIT 135 
#define  IPV6_RECVPKTINFO 134 
#define  IPV6_RECVRTHDR 133 
#define  IPV6_RECVTCLASS 132 
#define  IPV6_TCLASS 131 
#define  IPV6_UNICAST_HOPS 130 
#define  IPV6_USE_MIN_MTU 129 
#define  IPV6_V6ONLY 128 
 int icmp6_ctloutput (struct socket*,struct sockopt*) ; 
 int ip6_ctloutput (struct socket*,struct sockopt*) ; 
 scalar_t__ kauth_cred_issuser (int /*<<< orphan*/ ) ; 

int
icmp6_dgram_ctloutput(struct socket *so, struct sockopt *sopt)
{
	if (kauth_cred_issuser(so->so_cred))
		return icmp6_ctloutput(so, sopt);

	if (sopt->sopt_level == IPPROTO_ICMPV6) {
		switch (sopt->sopt_name) {
			case ICMP6_FILTER:
				return icmp6_ctloutput(so, sopt);
			default:
				return EPERM;
		}
	}

	if (sopt->sopt_level != IPPROTO_IPV6)
		return EINVAL;

	switch (sopt->sopt_name) {
		case IPV6_UNICAST_HOPS:
		case IPV6_CHECKSUM:
		case IPV6_V6ONLY:
		case IPV6_USE_MIN_MTU:
		case IPV6_RECVRTHDR:
		case IPV6_RECVPKTINFO:
		case IPV6_RECVHOPLIMIT:
		case IPV6_PATHMTU:
		case IPV6_PKTINFO:
		case IPV6_HOPLIMIT:
		case IPV6_HOPOPTS:
		case IPV6_DSTOPTS:
		case IPV6_MULTICAST_IF:
		case IPV6_MULTICAST_HOPS:
		case IPV6_MULTICAST_LOOP:
		case IPV6_JOIN_GROUP:
		case IPV6_LEAVE_GROUP:
		case IPV6_PORTRANGE:
		case IPV6_IPSEC_POLICY:
		case IPV6_RECVTCLASS:
		case IPV6_TCLASS:
		case IPV6_2292PKTOPTIONS:
		case IPV6_2292PKTINFO:
		case IPV6_2292HOPLIMIT:
		case IPV6_2292HOPOPTS:
		case IPV6_2292DSTOPTS:
		case IPV6_2292RTHDR:
		case IPV6_BOUND_IF:
		case IPV6_NO_IFT_CELLULAR:

			return ip6_ctloutput(so, sopt);

		default:
			return EPERM;
	}
}