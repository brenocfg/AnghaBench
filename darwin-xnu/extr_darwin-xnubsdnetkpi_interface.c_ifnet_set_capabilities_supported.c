#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  TYPE_1__* ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_5__ {int if_capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int IFCAP_VALID ; 
 int /*<<< orphan*/  ifnet_lock_done (TYPE_1__*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (TYPE_1__*) ; 

errno_t
ifnet_set_capabilities_supported(ifnet_t ifp, u_int32_t new_caps,
    u_int32_t mask)
{
	errno_t error = 0;
	int tmp;

	if (ifp == NULL)
		return (EINVAL);

	ifnet_lock_exclusive(ifp);
	tmp = (new_caps & mask) | (ifp->if_capabilities & ~mask);
	if ((tmp & ~IFCAP_VALID))
		error = EINVAL;
	else
		ifp->if_capabilities = tmp;
	ifnet_lock_done(ifp);

	return (error);
}