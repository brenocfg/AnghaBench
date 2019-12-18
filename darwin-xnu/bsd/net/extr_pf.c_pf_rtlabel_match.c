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
struct sockaddr_in6 {int sin6_family; int sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int sin_family; int sin_len; int /*<<< orphan*/  sin_addr; } ;
struct route_in6 {int dummy; } ;
struct route {int /*<<< orphan*/  ro_dst; } ;
struct pf_addr_wrap {int dummy; } ;
struct pf_addr {int /*<<< orphan*/  v6addr; int /*<<< orphan*/  v4addr; } ;
typedef  int sa_family_t ;
typedef  int /*<<< orphan*/  ro ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ROUTE_RELEASE (struct route*) ; 
 int /*<<< orphan*/  bzero (struct route*,int) ; 
 int /*<<< orphan*/  rtalloc (struct route*) ; 
 struct sockaddr_in* satosin (int /*<<< orphan*/ *) ; 

int
pf_rtlabel_match(struct pf_addr *addr, sa_family_t af, struct pf_addr_wrap *aw)
{
#pragma unused(aw)
	struct sockaddr_in	*dst;
#if INET6
	struct sockaddr_in6	*dst6;
	struct route_in6	 ro;
#else
	struct route		 ro;
#endif
	int			 ret = 0;

	bzero(&ro, sizeof (ro));
	switch (af) {
	case AF_INET:
		dst = satosin(&ro.ro_dst);
		dst->sin_family = AF_INET;
		dst->sin_len = sizeof (*dst);
		dst->sin_addr = addr->v4addr;
		break;
#if INET6
	case AF_INET6:
		dst6 = (struct sockaddr_in6 *)&ro.ro_dst;
		dst6->sin6_family = AF_INET6;
		dst6->sin6_len = sizeof (*dst6);
		dst6->sin6_addr = addr->v6addr;
		break;
#endif /* INET6 */
	default:
		return (0);
	}

	/* XXX: what is the point of this? */
	rtalloc((struct route *)&ro);

	ROUTE_RELEASE(&ro);

	return (ret);
}