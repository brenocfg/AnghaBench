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
struct ifnet {int if_eflags; } ;

/* Variables and functions */
 int IFEF_TXSTART ; 
 int /*<<< orphan*/  if_qflush (struct ifnet*,int /*<<< orphan*/ ) ; 

void
ifnet_purge(struct ifnet *ifp)
{
	if (ifp != NULL && (ifp->if_eflags & IFEF_TXSTART))
		if_qflush(ifp, 0);
}