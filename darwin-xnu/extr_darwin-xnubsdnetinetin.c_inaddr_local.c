#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; struct in_addr sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct rtentry {TYPE_2__* rt_ifp; TYPE_1__* rt_gateway; } ;
typedef  int /*<<< orphan*/  sin ;
struct TYPE_4__ {int if_flags; } ;
struct TYPE_3__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ AF_LINK ; 
 int IFF_LOOPBACK ; 
 scalar_t__ INADDR_LOOPBACK ; 
 scalar_t__ INADDR_MAX_LOCAL_GROUP ; 
 scalar_t__ INADDR_UNSPEC_GROUP ; 
 scalar_t__ IN_LINKLOCAL (scalar_t__) ; 
 int /*<<< orphan*/  RT_LOCK_SPIN (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int in_localaddr (struct in_addr) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 struct rtentry* rtalloc1 (struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtfree (struct rtentry*) ; 

int
inaddr_local(struct in_addr in)
{
	struct rtentry *rt;
	struct sockaddr_in sin;
	int local = 0;

	if (ntohl(in.s_addr) == INADDR_LOOPBACK ||
	    IN_LINKLOCAL(ntohl(in.s_addr))) {
		local = 1;
	} else if (ntohl(in.s_addr) >= INADDR_UNSPEC_GROUP &&
	    ntohl(in.s_addr) <= INADDR_MAX_LOCAL_GROUP) {
			local = 1;
	} else {
		sin.sin_family = AF_INET;
		sin.sin_len = sizeof (sin);
		sin.sin_addr = in;
		rt = rtalloc1((struct sockaddr *)&sin, 0, 0);

		if (rt != NULL) {
			RT_LOCK_SPIN(rt);
			if (rt->rt_gateway->sa_family == AF_LINK ||
			    (rt->rt_ifp->if_flags & IFF_LOOPBACK))
				local = 1;
			RT_UNLOCK(rt);
			rtfree(rt);
		} else {
			local = in_localaddr(in);
		}
	}
	return (local);
}