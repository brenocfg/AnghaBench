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
struct mbuf {int m_len; scalar_t__ m_next; } ;
struct ip6_pktopts {int dummy; } ;
struct cmsghdr {int cmsg_len; scalar_t__ cmsg_level; int /*<<< orphan*/  cmsg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 int CMSG_LEN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ IPPROTO_IPV6 ; 
 struct cmsghdr* M_FIRST_CMSGHDR (struct mbuf*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 struct cmsghdr* M_NXT_CMSGHDR (struct mbuf*,struct cmsghdr*) ; 
 int copypktopts (struct ip6_pktopts*,struct ip6_pktopts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_initpktopts (struct ip6_pktopts*) ; 
 int ip6_setpktopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ip6_pktopts*,int /*<<< orphan*/ ,int,int) ; 

int
ip6_setpktopts(struct mbuf *control, struct ip6_pktopts *opt,
    struct ip6_pktopts *stickyopt, int uproto)
{
	struct cmsghdr *cm = NULL;

	if (control == NULL || opt == NULL)
		return (EINVAL);

	ip6_initpktopts(opt);
	if (stickyopt) {
		int error;

		/*
		 * If stickyopt is provided, make a local copy of the options
		 * for this particular packet, then override them by ancillary
		 * objects.
		 * XXX: copypktopts() does not copy the cached route to a next
		 * hop (if any).  This is not very good in terms of efficiency,
		 * but we can allow this since this option should be rarely
		 * used.
		 */
		if ((error = copypktopts(opt, stickyopt, M_NOWAIT)) != 0)
			return (error);
	}

	/*
	 * XXX: Currently, we assume all the optional information is stored
	 * in a single mbuf.
	 */
	if (control->m_next)
		return (EINVAL);

	if (control->m_len < CMSG_LEN(0))
		return (EINVAL);

	for (cm = M_FIRST_CMSGHDR(control); cm != NULL;
	    cm = M_NXT_CMSGHDR(control, cm)) {
		int error;

		if (cm->cmsg_len < sizeof (struct cmsghdr) ||
		    cm->cmsg_len > control->m_len)
			return (EINVAL);
		if (cm->cmsg_level != IPPROTO_IPV6)
			continue;

		error = ip6_setpktopt(cm->cmsg_type, CMSG_DATA(cm),
		    cm->cmsg_len - CMSG_LEN(0), opt, 0, 1, uproto);
		if (error)
			return (error);
	}

	return (0);
}