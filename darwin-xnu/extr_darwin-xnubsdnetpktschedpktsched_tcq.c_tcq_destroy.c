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
struct tcq_if {struct ifclassq* tif_ifq; } ;
struct ifclassq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_UNLOCK (struct ifclassq*) ; 
 int tcq_destroy_locked (struct tcq_if*) ; 

int
tcq_destroy(struct tcq_if *tif)
{
	struct ifclassq *ifq = tif->tif_ifq;
	int err;

	IFCQ_LOCK(ifq);
	err = tcq_destroy_locked(tif);
	IFCQ_UNLOCK(ifq);

	return (err);
}