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
struct TYPE_2__ {int /*<<< orphan*/ * tqe_prev; int /*<<< orphan*/ * tqe_next; } ;
struct ifnet {TYPE_1__ if_detaching_link; } ;

/* Variables and functions */
 struct ifnet* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  dlil_if_lock_assert () ; 
 int /*<<< orphan*/  if_detaching_link ; 
 scalar_t__ ifnet_detaching_cnt ; 
 int /*<<< orphan*/  ifnet_detaching_head ; 

__attribute__((used)) static struct ifnet *
ifnet_detaching_dequeue(void)
{
	struct ifnet *ifp;

	dlil_if_lock_assert();

	ifp = TAILQ_FIRST(&ifnet_detaching_head);
	VERIFY(ifnet_detaching_cnt != 0 || ifp == NULL);
	if (ifp != NULL) {
		VERIFY(ifnet_detaching_cnt != 0);
		--ifnet_detaching_cnt;
		TAILQ_REMOVE(&ifnet_detaching_head, ifp, if_detaching_link);
		ifp->if_detaching_link.tqe_next = NULL;
		ifp->if_detaching_link.tqe_prev = NULL;
	}
	return (ifp);
}