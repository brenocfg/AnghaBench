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
struct in6_multi {scalar_t__ in6m_ifp; TYPE_1__* in6m_ifma; } ;
struct TYPE_2__ {scalar_t__ ifma_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ifnet_is_attached (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int
in6m_is_ifp_detached(const struct in6_multi *inm)
{
	VERIFY(inm->in6m_ifma != NULL);
	VERIFY(inm->in6m_ifp == inm->in6m_ifma->ifma_ifp);

	return (!ifnet_is_attached(inm->in6m_ifp, 0));
}