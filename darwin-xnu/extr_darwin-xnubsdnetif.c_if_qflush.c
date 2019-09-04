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
struct ifclassq {int dummy; } ;
struct ifnet {struct ifclassq if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_IS_EMPTY (struct ifclassq*) ; 
 scalar_t__ IFCQ_IS_ENABLED (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_PURGE (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_UNLOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 

void
if_qflush(struct ifnet *ifp, int ifq_locked)
{
	struct ifclassq *ifq = &ifp->if_snd;

	if (!ifq_locked)
		IFCQ_LOCK(ifq);

	if (IFCQ_IS_ENABLED(ifq))
		IFCQ_PURGE(ifq);

	VERIFY(IFCQ_IS_EMPTY(ifq));

	if (!ifq_locked)
		IFCQ_UNLOCK(ifq);
}