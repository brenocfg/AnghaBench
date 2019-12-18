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
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {scalar_t__ sa_family; } ;
struct mptses {TYPE_1__ mpte_src; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int mp_getaddr_v4 (struct socket*,struct sockaddr**,int) ; 
 int mp_getaddr_v6 (struct socket*,struct sockaddr**,int) ; 
 struct mptses* mpsotompte (struct socket*) ; 

int
mp_getpeeraddr(struct socket *mp_so, struct sockaddr **nam)
{
	struct mptses *mpte = mpsotompte(mp_so);

	if (mpte->mpte_src.sa_family == AF_INET || mpte->mpte_src.sa_family == 0)
		return mp_getaddr_v4(mp_so, nam, true);
	else if (mpte->mpte_src.sa_family == AF_INET6)
		return mp_getaddr_v6(mp_so, nam, true);
	else
		return (EINVAL);
}