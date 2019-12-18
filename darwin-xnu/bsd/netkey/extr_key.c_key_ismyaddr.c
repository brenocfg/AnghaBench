#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; int /*<<< orphan*/  sin_len; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int sa_family; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_9__ {TYPE_3__ sin_addr; int /*<<< orphan*/  sin_len; int /*<<< orphan*/  sin_family; } ;
struct TYPE_6__ {struct in_ifaddr* tqe_next; } ;
struct in_ifaddr {int /*<<< orphan*/  ia_ifa; TYPE_4__ ia_addr; TYPE_1__ ia_link; } ;
struct TYPE_10__ {struct in_ifaddr* tqh_first; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IFA_LOCK_SPIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFA_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_ifaddr_rwlock ; 
 TYPE_5__ in_ifaddrhead ; 
 int key_ismyaddr6 (struct sockaddr_in6*) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ ) ; 
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