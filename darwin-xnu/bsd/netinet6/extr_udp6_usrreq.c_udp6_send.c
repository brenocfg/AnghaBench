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
struct socket {scalar_t__ so_cfil_db; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {int sa_len; scalar_t__ sa_family; } ;
struct proc {int dummy; } ;
struct pr_usrreqs {int (* pru_send ) (struct socket*,int,struct mbuf*,struct sockaddr*,struct mbuf*,struct proc*) ;} ;
struct mbuf {int dummy; } ;
struct m_tag {int dummy; } ;
struct inpcb {int inp_flags; int inp_vflag; int /*<<< orphan*/  in6p_faddr; } ;
struct TYPE_2__ {struct pr_usrreqs* pr_usrreqs; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int IN6P_IPV6_V6ONLY ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (int /*<<< orphan*/ *) ; 
 int INP_IPV4 ; 
 size_t IPPROTO_UDP ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 struct m_tag* cfil_udp_get_socket_state (struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr**) ; 
 int flow_divert_implicit_data_out (struct socket*,int,struct mbuf*,struct sockaddr*,struct mbuf*,struct proc*) ; 
 int /*<<< orphan*/  in6_sin6_2_sin_in_sock (struct sockaddr*) ; 
 scalar_t__ ip6_mapped_addr_on ; 
 TYPE_1__** ip_protox ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_tag_free (struct m_tag*) ; 
 int necp_socket_should_use_flow_divert (struct inpcb*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int stub1 (struct socket*,int,struct mbuf*,struct sockaddr*,struct mbuf*,struct proc*) ; 
 int udp6_output (struct inpcb*,struct mbuf*,struct sockaddr*,struct mbuf*,struct proc*) ; 

__attribute__((used)) static int
udp6_send(struct socket *so, int flags, struct mbuf *m, struct sockaddr *addr,
    struct mbuf *control, struct proc *p)
{
	struct inpcb *inp;
	int error = 0;
#if defined(NECP) && defined(FLOW_DIVERT)
	int should_use_flow_divert = 0;
#endif /* defined(NECP) && defined(FLOW_DIVERT) */
#if CONTENT_FILTER
	struct m_tag *cfil_tag = NULL;
	struct sockaddr *cfil_faddr = NULL;
#endif

	inp = sotoinpcb(so);
	if (inp == NULL) {
		error = EINVAL;
		goto bad;
	}

#if CONTENT_FILTER
	//If socket is subject to UDP Content Filter and unconnected, get addr from tag.
	if (so->so_cfil_db && !addr && IN6_IS_ADDR_UNSPECIFIED(&inp->in6p_faddr)) {
		cfil_tag = cfil_udp_get_socket_state(m, NULL, NULL, &cfil_faddr);
		if (cfil_tag) {
			addr = (struct sockaddr *)cfil_faddr;
		}
	}
#endif

#if defined(NECP) && defined(FLOW_DIVERT)
	should_use_flow_divert = necp_socket_should_use_flow_divert(inp);
#endif /* defined(NECP) && defined(FLOW_DIVERT) */

	if (addr != NULL) {
		if (addr->sa_len != sizeof (struct sockaddr_in6)) {
			error = EINVAL;
			goto bad;
		}
		if (addr->sa_family != AF_INET6) {
			error = EAFNOSUPPORT;
			goto bad;
		}
	}

	if (ip6_mapped_addr_on || (inp->inp_flags & IN6P_IPV6_V6ONLY) == 0) {
		int hasv4addr;
		struct sockaddr_in6 *sin6 = NULL;

		if (addr == NULL) {
			hasv4addr = (inp->inp_vflag & INP_IPV4);
		} else {
			sin6 = (struct sockaddr_in6 *)(void *)addr;
			hasv4addr =
			    IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr) ? 1 : 0;
		}
		if (hasv4addr) {
			struct pr_usrreqs *pru;

			if (sin6 != NULL)
				in6_sin6_2_sin_in_sock(addr);
#if defined(NECP) && defined(FLOW_DIVERT)
			if (should_use_flow_divert) {
				goto do_flow_divert;
			}
#endif /* defined(NECP) && defined(FLOW_DIVERT) */
			pru = ip_protox[IPPROTO_UDP]->pr_usrreqs;
			error = ((*pru->pru_send)(so, flags, m, addr,
			    control, p));
#if CONTENT_FILTER
			if (cfil_tag)
				m_tag_free(cfil_tag);
#endif
			/* addr will just be freed in sendit(). */
			return (error);
		}
	}

#if defined(NECP) && defined(FLOW_DIVERT)
do_flow_divert:
	if (should_use_flow_divert) {
		/* Implicit connect */
		error = flow_divert_implicit_data_out(so, flags, m, addr, control, p);
#if CONTENT_FILTER
		if (cfil_tag)
			m_tag_free(cfil_tag);
#endif
		return error;
	}
#endif /* defined(NECP) && defined(FLOW_DIVERT) */

	error = udp6_output(inp, m, addr, control, p);
#if CONTENT_FILTER
	if (cfil_tag)
		m_tag_free(cfil_tag);
#endif
	return error;

bad:
	VERIFY(error != 0);

	if (m != NULL)
		m_freem(m);
	if (control != NULL)
		m_freem(control);
#if CONTENT_FILTER
	if (cfil_tag)
		m_tag_free(cfil_tag);
#endif
	return (error);
}