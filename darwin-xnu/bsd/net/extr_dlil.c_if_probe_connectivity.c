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
typedef  int u_int32_t ;
struct ifnet {int /*<<< orphan*/  if_eflags; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IFEF_PROBE_CONNECTIVITY ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int /*<<< orphan*/  necp_update_all_clients () ; 
 int /*<<< orphan*/  tcp_probe_connectivity (struct ifnet*,int) ; 

errno_t
if_probe_connectivity(struct ifnet *ifp, u_int32_t conn_probe)
{
	ifnet_lock_exclusive(ifp);
	if (conn_probe > 1) {
		ifnet_lock_done(ifp);
		return (EINVAL);
	}
	if (conn_probe == 0)
		ifp->if_eflags &= ~IFEF_PROBE_CONNECTIVITY;
	else
		ifp->if_eflags |= IFEF_PROBE_CONNECTIVITY;
	ifnet_lock_done(ifp);

#if NECP
	necp_update_all_clients();
#endif /* NECP */

	tcp_probe_connectivity(ifp, conn_probe);
	return (0);
}