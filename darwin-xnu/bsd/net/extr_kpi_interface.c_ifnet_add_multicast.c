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
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  int /*<<< orphan*/  ifmultiaddr_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  if_addmulti_anon (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ *) ; 

errno_t
ifnet_add_multicast(ifnet_t interface, const struct sockaddr *maddr,
    ifmultiaddr_t *ifmap)
{
	if (interface == NULL || maddr == NULL)
		return (EINVAL);

	/* Don't let users screw up protocols' entries. */
	if (maddr->sa_family != AF_UNSPEC && maddr->sa_family != AF_LINK)
		return (EINVAL);

	return (if_addmulti_anon(interface, maddr, ifmap));
}