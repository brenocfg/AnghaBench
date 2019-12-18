#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {scalar_t__ sa_len; } ;
struct TYPE_2__ {scalar_t__ sa_len; } ;
struct ndrv_multiaddr {TYPE_1__ addr; struct ndrv_multiaddr* next; } ;
struct ndrv_cb {struct ndrv_multiaddr* nd_multiaddrs; } ;

/* Variables and functions */
 scalar_t__ bcmp (TYPE_1__*,struct sockaddr*,scalar_t__) ; 

__attribute__((used)) static struct ndrv_multiaddr*
ndrv_have_multicast(struct ndrv_cb *np, struct sockaddr* inAddr)
{
    struct ndrv_multiaddr*	cur;
    for (cur = np->nd_multiaddrs; cur != NULL; cur = cur->next)
    {

        if ((inAddr->sa_len == cur->addr.sa_len) &&
            (bcmp(&cur->addr, inAddr, inAddr->sa_len) == 0))
        {
            // Found a match
            return cur;
        }
    }

    return NULL;
}