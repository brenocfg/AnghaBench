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
struct ifnet_poll_params {int dummy; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  dlil_rxpoll_set_params (struct ifnet*,struct ifnet_poll_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_decr_iorefcnt (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_is_attached (struct ifnet*,int) ; 

errno_t
ifnet_set_poll_params(struct ifnet *ifp, struct ifnet_poll_params *p)
{
	errno_t err;

	if (ifp == NULL)
		return (EINVAL);
	else if (!ifnet_is_attached(ifp, 1))
		return (ENXIO);

	err = dlil_rxpoll_set_params(ifp, p, FALSE);

	/* Release the io ref count */
	ifnet_decr_iorefcnt(ifp);

	return (err);
}