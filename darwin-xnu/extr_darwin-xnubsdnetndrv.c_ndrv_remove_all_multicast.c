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
struct ndrv_multiaddr {int /*<<< orphan*/  ifma; struct ndrv_multiaddr* next; } ;
struct ndrv_cb {struct ndrv_multiaddr* nd_multiaddrs; int /*<<< orphan*/ * nd_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct ndrv_multiaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IFADDR ; 
 int /*<<< orphan*/  ifmaddr_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_remove_multicast (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ndrv_remove_all_multicast(struct ndrv_cb* np)
{
    struct ndrv_multiaddr*	cur;

    if (np->nd_if != NULL)
    {
        while (np->nd_multiaddrs != NULL)
        {
            cur = np->nd_multiaddrs;
            np->nd_multiaddrs = cur->next;

            ifnet_remove_multicast(cur->ifma);
            ifmaddr_release(cur->ifma);
            FREE(cur, M_IFADDR);
        }
    }
}