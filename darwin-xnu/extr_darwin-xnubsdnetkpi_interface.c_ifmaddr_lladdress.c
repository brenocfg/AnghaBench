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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sockaddr {int dummy; } ;
struct ifmultiaddr {int dummy; } ;
typedef  TYPE_1__* ifmultiaddr_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_3__ {struct ifmultiaddr* ifma_ll; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  ifmaddr_address (struct ifmultiaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 

errno_t
ifmaddr_lladdress(ifmultiaddr_t ifma, struct sockaddr *out_addr,
    u_int32_t addr_size)
{
	struct ifmultiaddr *ifma_ll;

	if (ifma == NULL || out_addr == NULL)
		return (EINVAL);
	if ((ifma_ll = ifma->ifma_ll) == NULL)
		return (ENOTSUP);

	return (ifmaddr_address(ifma_ll, out_addr, addr_size));
}