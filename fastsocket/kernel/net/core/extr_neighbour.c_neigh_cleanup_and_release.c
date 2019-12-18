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
struct neighbour {TYPE_1__* parms; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* neigh_cleanup ) (struct neighbour*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RTM_DELNEIGH ; 
 int /*<<< orphan*/  __neigh_notify (struct neighbour*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  stub1 (struct neighbour*) ; 

__attribute__((used)) static void neigh_cleanup_and_release(struct neighbour *neigh)
{
	if (neigh->parms->neigh_cleanup)
		neigh->parms->neigh_cleanup(neigh);

	__neigh_notify(neigh, RTM_DELNEIGH, 0);
	neigh_release(neigh);
}