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
typedef  int /*<<< orphan*/  uuid_t ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int if_delete_netagent_locked (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 

int
if_delete_netagent(struct ifnet *ifp, uuid_t remove_agent_uuid)
{
	VERIFY(ifp != NULL);

	ifnet_lock_exclusive(ifp);

	int error = if_delete_netagent_locked(ifp, remove_agent_uuid);

	ifnet_lock_done(ifp);

	return (error);
}