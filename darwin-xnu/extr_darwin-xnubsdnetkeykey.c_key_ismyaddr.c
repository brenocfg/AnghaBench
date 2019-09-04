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
struct sockaddr {int sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 

int
key_ismyaddr(
			 struct sockaddr *sa)
{
#if INET
	struct sockaddr_in *sin;
	struct in_ifaddr *ia;
#endif
	
	/* sanity check */
	if (sa == NULL)
		panic("key_ismyaddr: NULL pointer is passed.\n");
	
	switch (sa->sa_family) {
#if INET
		case AF_INET:
			lck_rw_lock_shared(in_ifaddr_rwlock);
			sin = (struct sockaddr_in *)(void *)sa;
			for (ia = in_ifaddrhead.tqh_first; ia;
				 ia = ia->ia_link.tqe_next) {
				IFA_LOCK_SPIN(&ia->ia_ifa);
				if (sin->sin_family == ia->ia_addr.sin_family &&
					sin->sin_len == ia->ia_addr.sin_len &&
					sin->sin_addr.s_addr == ia->ia_addr.sin_addr.s_addr)
				{
					IFA_UNLOCK(&ia->ia_ifa);
					lck_rw_done(in_ifaddr_rwlock);
					return 1;
				}
				IFA_UNLOCK(&ia->ia_ifa);
			}
			lck_rw_done(in_ifaddr_rwlock);
			break;
#endif
#if INET6
		case AF_INET6:
			return key_ismyaddr6((struct sockaddr_in6 *)(void *)sa);
#endif
	}
	
	return 0;
}