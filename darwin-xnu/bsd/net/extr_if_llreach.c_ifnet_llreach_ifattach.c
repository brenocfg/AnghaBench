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
struct ifnet {int /*<<< orphan*/  if_llreach_lock; int /*<<< orphan*/  if_ll_srcs; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 

void
ifnet_llreach_ifattach(struct ifnet *ifp, boolean_t reuse)
{
	lck_rw_lock_exclusive(&ifp->if_llreach_lock);
	/* Initialize link-layer source tree (if not already) */
	if (!reuse)
		RB_INIT(&ifp->if_ll_srcs);
	lck_rw_done(&ifp->if_llreach_lock);
}