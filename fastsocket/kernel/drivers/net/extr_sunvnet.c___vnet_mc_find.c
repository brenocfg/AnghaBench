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
typedef  int /*<<< orphan*/  u8 ;
struct vnet_mcast_entry {int /*<<< orphan*/  addr; struct vnet_mcast_entry* next; } ;
struct vnet {struct vnet_mcast_entry* mcast_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vnet_mcast_entry *__vnet_mc_find(struct vnet *vp, u8 *addr)
{
	struct vnet_mcast_entry *m;

	for (m = vp->mcast_list; m; m = m->next) {
		if (!memcmp(m->addr, addr, ETH_ALEN))
			return m;
	}
	return NULL;
}