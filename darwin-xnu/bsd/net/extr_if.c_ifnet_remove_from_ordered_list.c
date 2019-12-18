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
struct ifnet {TYPE_1__ if_ordered_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ if_ordered_count ; 
 int /*<<< orphan*/  if_ordered_link ; 
 int /*<<< orphan*/  ifnet_head_assert_exclusive () ; 
 int /*<<< orphan*/  ifnet_ordered_head ; 

void
ifnet_remove_from_ordered_list(struct ifnet *ifp)
{
	ifnet_head_assert_exclusive();

	// Remove from list
	TAILQ_REMOVE(&ifnet_ordered_head, ifp, if_ordered_link);
	ifp->if_ordered_link.tqe_next = NULL;
	ifp->if_ordered_link.tqe_prev = NULL;

	// Update ordered count
	VERIFY(if_ordered_count > 0);
	if_ordered_count--;
}