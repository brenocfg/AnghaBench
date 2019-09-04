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
struct sockaddr {scalar_t__ sa_len; } ;
struct rt_addrinfo {int rti_addrs; struct sockaddr** rti_info; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE32 (scalar_t__,struct sockaddr*) ; 
 int EINVAL ; 
 int RTAX_MAX ; 
 int /*<<< orphan*/  bzero (struct sockaddr**,int) ; 
 struct sockaddr sa_zero ; 

__attribute__((used)) static int
rt_xaddrs(caddr_t cp, caddr_t cplim, struct rt_addrinfo *rtinfo)
{
	struct sockaddr *sa;
	int i;

	bzero(rtinfo->rti_info, sizeof (rtinfo->rti_info));
	for (i = 0; (i < RTAX_MAX) && (cp < cplim); i++) {
		if ((rtinfo->rti_addrs & (1 << i)) == 0)
			continue;
		sa = (struct sockaddr *)cp;
		/*
		 * It won't fit.
		 */
		if ((cp + sa->sa_len) > cplim)
			return (EINVAL);
		/*
		 * there are no more.. quit now
		 * If there are more bits, they are in error.
		 * I've seen this. route(1) can evidently generate these.
		 * This causes kernel to core dump.
		 * for compatibility, If we see this, point to a safe address.
		 */
		if (sa->sa_len == 0) {
			rtinfo->rti_info[i] = &sa_zero;
			return (0); /* should be EINVAL but for compat */
		}
		/* accept it */
		rtinfo->rti_info[i] = sa;
		ADVANCE32(cp, sa);
	}
	return (0);
}