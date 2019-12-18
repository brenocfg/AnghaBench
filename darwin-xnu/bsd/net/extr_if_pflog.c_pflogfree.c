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
struct ifnet {int /*<<< orphan*/ * if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  if_clone_softc_deallocate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_release (struct ifnet*) ; 
 int /*<<< orphan*/  pflog_cloner ; 

__attribute__((used)) static void
pflogfree(struct ifnet *ifp)
{
	if_clone_softc_deallocate(&pflog_cloner, ifp->if_softc);
	ifp->if_softc = NULL;
	(void) ifnet_release(ifp);
}