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
typedef  scalar_t__ u_int32_t ;
struct sockaddr {int dummy; } ;
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EJUSTRETURN ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static errno_t
ifp_if_framer_extended(struct ifnet *ifp, struct mbuf **m,
    const struct sockaddr *sa, const char *ll, const char *t,
    u_int32_t *pre, u_int32_t *post)
{
#pragma unused(ifp, sa, ll, t)
	m_freem(*m);
	*m = NULL;

	if (pre != NULL)
		*pre = 0;
	if (post != NULL)
		*post = 0;

	return (EJUSTRETURN);
}