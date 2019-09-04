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
struct sockopt {int dummy; } ;
struct socket {int dummy; } ;
struct mbuf {scalar_t__ m_len; } ;
struct ip6_pktopts {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  FREE (struct ip6_pktopts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IP6OPT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SOCK_PROTO (struct socket*) ; 
 struct ip6_pktopts* _MALLOC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_clearpktopts (struct ip6_pktopts*,int) ; 
 int ip6_setpktopts (struct mbuf*,struct ip6_pktopts*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ip6_pcbopts(struct ip6_pktopts **pktopt, struct mbuf *m, struct socket *so,
    struct sockopt *sopt)
{
#pragma unused(sopt)
	struct ip6_pktopts *opt = *pktopt;
	int error = 0;

	/* turn off any old options. */
	if (opt != NULL) {
#if DIAGNOSTIC
		if (opt->ip6po_pktinfo || opt->ip6po_nexthop ||
		    opt->ip6po_hbh || opt->ip6po_dest1 || opt->ip6po_dest2 ||
		    opt->ip6po_rhinfo.ip6po_rhi_rthdr)
			printf("%s: all specified options are cleared.\n",
			    __func__);
#endif
		ip6_clearpktopts(opt, -1);
	} else {
		opt = _MALLOC(sizeof (*opt), M_IP6OPT, M_WAITOK);
		if (opt == NULL)
			return (ENOBUFS);
	}
	*pktopt = NULL;

	if (m == NULL || m->m_len == 0) {
		/*
		 * Only turning off any previous options, regardless of
		 * whether the opt is just created or given.
		 */
		if (opt != NULL)
			FREE(opt, M_IP6OPT);
		return (0);
	}

	/*  set options specified by user. */
	if ((error = ip6_setpktopts(m, opt, NULL, SOCK_PROTO(so))) != 0) {
		ip6_clearpktopts(opt, -1); /* XXX: discard all options */
		FREE(opt, M_IP6OPT);
		return (error);
	}
	*pktopt = opt;
	return (0);
}