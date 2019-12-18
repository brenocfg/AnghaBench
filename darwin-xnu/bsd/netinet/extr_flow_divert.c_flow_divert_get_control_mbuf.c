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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct inpcb {int inp_vflag; int inp_flags; } ;
struct in_addr {int dummy; } ;
struct in6_pktinfo {scalar_t__ ipi6_ifindex; int /*<<< orphan*/  ipi6_addr; } ;
struct in6_addr {int dummy; } ;
struct flow_divert_pcb {scalar_t__ local_address; int /*<<< orphan*/  so; } ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int IN6P_PKTINFO ; 
 int INP_IPV4 ; 
 int INP_IPV6 ; 
 int INP_RECVDSTADDR ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_PKTINFO ; 
 int /*<<< orphan*/  IP_RECVDSTADDR ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sbcreatecontrol (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mbuf_t
flow_divert_get_control_mbuf(struct flow_divert_pcb *fd_cb)
{
	struct inpcb *inp = sotoinpcb(fd_cb->so);
	if (inp->inp_vflag & INP_IPV4 && inp->inp_flags & INP_RECVDSTADDR) {
		struct sockaddr_in *sin = (struct sockaddr_in *)(void *)fd_cb->local_address;

		return sbcreatecontrol((caddr_t) &sin->sin_addr, sizeof(struct in_addr), IP_RECVDSTADDR, IPPROTO_IP);
	} else if (inp->inp_vflag & INP_IPV6 && (inp->inp_flags & IN6P_PKTINFO) != 0) {
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)(void *)fd_cb->local_address;
		struct in6_pktinfo pi6;

		bcopy(&sin6->sin6_addr, &pi6.ipi6_addr, sizeof (struct in6_addr));
		pi6.ipi6_ifindex = 0;
		return sbcreatecontrol((caddr_t)&pi6, sizeof (struct in6_pktinfo), IPV6_PKTINFO, IPPROTO_IPV6);
	}
	return (NULL);
}