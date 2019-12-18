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
struct llentry {int /*<<< orphan*/  r_flags; int /*<<< orphan*/  la_flags; int /*<<< orphan*/  ll_addr; } ;
struct ifnet {int /*<<< orphan*/  if_addrlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLE_VALID ; 
 int /*<<< orphan*/  RLLE_VALID ; 
 int /*<<< orphan*/  bcopy (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
lltable_set_entry_addr(struct ifnet *ifp, struct llentry *lle,
    const char *ll_addr)
{
	bcopy(ll_addr, &lle->ll_addr, ifp->if_addrlen);
	lle->la_flags |= LLE_VALID;
	lle->r_flags |= RLLE_VALID;
}