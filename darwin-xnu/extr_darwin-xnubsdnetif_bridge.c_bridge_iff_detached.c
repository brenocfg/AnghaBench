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
struct bridge_iflist {int dummy; } ;
typedef  int /*<<< orphan*/  ifnet_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  _FREE (struct bridge_iflist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_ifdetach (struct bridge_iflist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bridge_iff_detached(void *cookie, ifnet_t ifp)
{
	struct bridge_iflist *bif = (struct bridge_iflist *)cookie;

#if BRIDGE_DEBUG
	if (if_bridge_debug & BR_DBGF_LIFECYCLE)
		printf("%s: %s\n", __func__, ifp->if_xname);
#endif /* BRIDGE_DEBUG */

	bridge_ifdetach(bif, ifp);

	_FREE(bif, M_DEVBUF);
}