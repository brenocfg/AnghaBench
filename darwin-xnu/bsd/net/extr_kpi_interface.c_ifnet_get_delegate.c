#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_10__ {TYPE_2__* ifp; } ;
struct TYPE_11__ {TYPE_1__ if_delegated; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  ifnet_decr_iorefcnt (TYPE_2__*) ; 
 int /*<<< orphan*/  ifnet_is_attached (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ifnet_lock_done (TYPE_2__*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (TYPE_2__*) ; 
 int /*<<< orphan*/  ifnet_reference (TYPE_2__*) ; 

errno_t
ifnet_get_delegate(ifnet_t ifp, ifnet_t *pdelegated_ifp)
{
	if (ifp == NULL || pdelegated_ifp == NULL)
		return (EINVAL);
	else if (!ifnet_is_attached(ifp, 1))
		return (ENXIO);

	ifnet_lock_shared(ifp);
	if (ifp->if_delegated.ifp != NULL)
		ifnet_reference(ifp->if_delegated.ifp);
	*pdelegated_ifp = ifp->if_delegated.ifp;
	ifnet_lock_done(ifp);

	/* Release the io ref count */
	ifnet_decr_iorefcnt(ifp);

	return (0);
}