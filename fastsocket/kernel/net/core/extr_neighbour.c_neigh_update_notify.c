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
struct neighbour {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_NEIGH_UPDATE ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 int /*<<< orphan*/  __neigh_notify (struct neighbour*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_netevent_notifiers (int /*<<< orphan*/ ,struct neighbour*) ; 

__attribute__((used)) static void neigh_update_notify(struct neighbour *neigh)
{
	call_netevent_notifiers(NETEVENT_NEIGH_UPDATE, neigh);
	__neigh_notify(neigh, RTM_NEWNEIGH, 0);
}