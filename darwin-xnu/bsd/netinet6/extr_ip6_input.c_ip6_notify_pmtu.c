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
typedef  int /*<<< orphan*/  u_int32_t ;
struct socket {int /*<<< orphan*/  so_rcv; TYPE_1__* so_proto; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct mbuf {int dummy; } ;
struct ip6_mtuinfo {struct sockaddr_in6 ip6m_addr; int /*<<< orphan*/  ip6m_mtu; } ;
struct inpcb {int inp_flags; int /*<<< orphan*/  in6p_faddr; struct socket* inp_socket; } ;
typedef  int /*<<< orphan*/  mtuctl ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {scalar_t__ pr_protocol; } ;

/* Variables and functions */
 int IN6P_MTU ; 
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  IPV6_PATHMTU ; 
 int /*<<< orphan*/  SA (struct sockaddr_in6*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (struct ip6_mtuinfo*,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ sa6_recoverscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 scalar_t__ sbappendaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ *) ; 
 struct mbuf* sbcreatecontrol (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorwakeup (struct socket*) ; 

void
ip6_notify_pmtu(struct inpcb *in6p, struct sockaddr_in6 *dst, u_int32_t *mtu)
{
	struct socket *so;
	struct mbuf *m_mtu;
	struct ip6_mtuinfo mtuctl;

	so =  in6p->inp_socket;

	if ((in6p->inp_flags & IN6P_MTU) == 0)
		return;

	if (mtu == NULL)
		return;

#ifdef DIAGNOSTIC
	if (so == NULL) {		/* I believe this is impossible */
		panic("ip6_notify_pmtu: socket is NULL");
		/* NOTREACHED */
	}
#endif

	if (IN6_IS_ADDR_UNSPECIFIED(&in6p->in6p_faddr) &&
	    (so->so_proto == NULL || so->so_proto->pr_protocol == IPPROTO_TCP))
		return;

	if (!IN6_IS_ADDR_UNSPECIFIED(&in6p->in6p_faddr) &&
	    !IN6_ARE_ADDR_EQUAL(&in6p->in6p_faddr, &dst->sin6_addr))
		return;

	bzero(&mtuctl, sizeof (mtuctl));	/* zero-clear for safety */
	mtuctl.ip6m_mtu = *mtu;
	mtuctl.ip6m_addr = *dst;
	if (sa6_recoverscope(&mtuctl.ip6m_addr, TRUE))
		return;

	if ((m_mtu = sbcreatecontrol((caddr_t)&mtuctl, sizeof (mtuctl),
	    IPV6_PATHMTU, IPPROTO_IPV6)) == NULL)
		return;

	if (sbappendaddr(&so->so_rcv, SA(dst), NULL, m_mtu, NULL) == 0) {
		m_freem(m_mtu);
		/* XXX: should count statistics */
	} else {
		sorwakeup(so);
	}
}