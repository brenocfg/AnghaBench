#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {scalar_t__ sa_family; } ;
typedef  TYPE_1__* ifmultiaddr_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_3__ {int /*<<< orphan*/  ifma_ifp; struct sockaddr* ifma_addr; } ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  if_delmulti_anon (int /*<<< orphan*/ ,struct sockaddr*) ; 

errno_t
ifnet_remove_multicast(ifmultiaddr_t ifma)
{
	struct sockaddr *maddr;

	if (ifma == NULL)
		return (EINVAL);

	maddr = ifma->ifma_addr;
	/* Don't let users screw up protocols' entries. */
	if (maddr->sa_family != AF_UNSPEC && maddr->sa_family != AF_LINK)
		return (EINVAL);

	return (if_delmulti_anon(ifma->ifma_ifp, maddr));
}