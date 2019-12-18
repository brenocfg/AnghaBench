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
struct qfq_if {struct ifclassq* qif_ifq; } ;
struct ifclassq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_UNLOCK (struct ifclassq*) ; 
 int qfq_destroy_locked (struct qfq_if*) ; 

int
qfq_destroy(struct qfq_if *qif)
{
	struct ifclassq *ifq = qif->qif_ifq;
	int err;

	IFCQ_LOCK(ifq);
	err = qfq_destroy_locked(qif);
	IFCQ_UNLOCK(ifq);

	return (err);
}