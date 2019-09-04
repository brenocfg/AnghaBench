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
typedef  int /*<<< orphan*/  u_char ;
struct ip6_pktopts {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  M_IP6OPT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct ip6_pktopts* _MALLOC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_initpktopts (struct ip6_pktopts*) ; 
 int ip6_setpktopt (int,int /*<<< orphan*/ *,int,struct ip6_pktopts*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ip6_pcbopt(int optname, u_char *buf, int len, struct ip6_pktopts **pktopt,
    int uproto)
{
	struct ip6_pktopts *opt;

	opt = *pktopt;
	if (opt == NULL) {
		opt = _MALLOC(sizeof (*opt), M_IP6OPT, M_WAITOK);
		if (opt == NULL)
			return (ENOBUFS);
		ip6_initpktopts(opt);
		*pktopt = opt;
	}

	return (ip6_setpktopt(optname, buf, len, opt, 1, 0, uproto));
}